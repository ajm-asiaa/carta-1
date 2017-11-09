#include "CartaLib/Hooks/Initialize.h"
#include "CartaLib/Hooks/PixelToPercentileHook.h"
#include "plugins/CasaImageLoader/CCImage.h"
#include "plugins/PercentileHistogram/PercentileHistogramPlugin.h"
#include "plugins/PercentileHistogram/PercentileHistogram.h"
#include <QDebug>


bool PercentileHistogramPlugin::handleHook( BaseHook & hookData ){
    if ( hookData.is < Carta::Lib::Hooks::Initialize > () ) {
        return true;
    }
    
    else if ( hookData.is < Carta::Lib::Hooks::PixelToPercentileHook > () ) {
        Carta::Lib::Hooks::PixelToPercentileHook & hook
            = static_cast <Carta::Lib::Hooks::PixelToPercentileHook & > ( hookData );
        
        // TODO this is currently unused, but we should use it to pick a plugin (maybe)
        std::shared_ptr<Carta::Lib::Image::ImageInterface> image = hook.paramsPtr->m_image;
                
        hook.result = PercentileHistogram(m_numberOfBins);
        
        return true;
    }
    
    qWarning() << "Percentile histogram plugin doesn't know how to handle this hook";
    return false;
} // handleHook


std::vector < HookId > PercentileHistogramPlugin::getInitialHookList() {
    return {
        Carta::Lib::Hooks::Initialize::staticId,
        Carta::Lib::Hooks::PixelToPercentileHook::staticId
    };
}

void PercentileHistogramPlugin::initialize( const IPlugin::InitInfo & initInfo )
{
    qDebug() << "PercentileHistogramPlugin initializing...";
    QJsonDocument doc( initInfo.json );
    qDebug() << doc.toJson();
    
    try {
        m_numberOfBins = initInfo.json.value( "numberOfBins").toInt();
    } catch (const QString& error) {
        qCritical() << "No valid numberOfBins value specified for percentile histogram plugin.";
    }
        
    if( m_numberOfBins <= 0) {
        qCritical() << "No valid numberOfBins value specified for percentile histogram plugin. Must be a positive integer.";
    }
}

