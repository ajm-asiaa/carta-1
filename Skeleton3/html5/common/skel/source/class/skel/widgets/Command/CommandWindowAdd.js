/**
 * Command to show/hide the menu bar.
 */

qx.Class.define("skel.widgets.Command.CommandWindowAdd", {
    extend : skel.widgets.Command.Command,
    type : "singleton",

    construct : function() {
        var path = skel.widgets.Path.getInstance();
        var cmd = path.SEP_COMMAND + "addWindow";
        this.base( arguments, "Add Window", cmd );
    },
    
    members : {
        
        doAction : function( vals, objectIDs, undoCB ){
            var path = skel.widgets.Path.getInstance();
            var params = "row:"+vals.row+",col:"+vals.col;
            this.sendCommand( path.LAYOUT, params, undoCB );
        },
        
        getType : function(){
            return skel.widgets.Command.Command.TYPE_BUTTON;
        }
    }
});