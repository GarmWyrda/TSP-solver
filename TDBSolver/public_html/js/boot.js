// création des alias/paths
require.config({
    paths: {
        jQuery: 'http://code.jquery.com/jquery-1.10.1.min',
        async: "../lib/async",
        logger : "interface/Logger",
        map : "model/Map",
        loadplace : "model/loadplace",
        GoogleMaps : "../lib/GoogleMaps",
        ui : "interface/Ui",
        listener: "interface/Listener",
        environment: "model/Environment",
        point : "model/Point",
        way : "model/Way"
    },
    shim: {
        'jQuery': {
            exports: '$'
        }    
    }
});

//Le loadplace sera a supprimer du require à terme
require(["logger","environment","ui","loadplace"], init);

function init(Logger) {
        $.getJSON("ressources/emplacements.txt",function(data){
           var length = data.length;
           var string = "";
           for(var i = 0;i<length+1;i++){
               string += "<option value=" + i + ">" + i + "</option> ";
           }
           $("#list").html(string);
        });
        Logger.log("alert-success","Loading successful");
}
 

