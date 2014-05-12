// création des alias/paths
require.config({
    paths: {
        jQuery: 'http://code.jquery.com/jquery-1.10.1.min',
        async: "../lib/async",
        logger : "interface/Logger",
        map : "model/Map",
        GoogleMaps : "../lib/GoogleMaps",
        ui : "interface/Ui",
        distanceMatrix :"model/DistanceMatrix",
        listener: "interface/Listener",
        environment: "model/Environment",
        point : "model/Point",
        way : "model/Way",
        server_request: "connexion-server/server-request"
    },
    shim: {
        'jQuery': {
            exports: '$'
        }    
    }
});

require(["logger","environment","distanceMatrix", "ui"], init);


function init(Logger) {
        $.getJSON("ressources/emplacements.txt")
            .done(function(data){
                var length = data.length;
                var string = "";
                for(var i = 0;i<length+1;i++){
                    string += "<option value=" + i + ">" + i + "</option> ";
                }
                $("#list").html(string);
                Logger.log(Logger.success,"Loading successful");
            })
            .fail(function( jqxhr, textStatus, error ) {
                var err = "Request Failed: " + textStatus + ", " + error;
                Logger.log(Logger.error,err);
        });
}
 