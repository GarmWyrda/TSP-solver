// création des alias/paths
require.config({
    paths: {
        jQuery: 'http://code.jquery.com/jquery-1.10.1.min',
        async: "../lib/async"
    },
    shim: {
        'jQuery': {
            exports: 'jQuery'
        }    
    }
});

require(["jQuery","GoogleMaps","printMap","loadUI","loadplace","log"], init);

function init() {
        $.getJSON("ressources/emplacements.txt",function(data){
           var length = data.length;
           var string = "";
           for(var i = 0;i<length+1;i++){
               string += "<option value=" + i + ">" + i + "</option> ";
           }
           $("#list").html(string);
        });
        Logger.log(Logger.success,"Loading successful");
}
 

