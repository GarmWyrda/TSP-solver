define('server_interaction',['jQuery','logger'],function($,Logger){
    var playTSP = function(){
        if (window.WebSocket && (serverConnection.isConnected === true) ){
            //interaction avec le serveur
        }else{
            Logger.log(Logger.error,"Serveur non connecté");
        }
    };
    
    var pauseTSP = function(){
    if (window.WebSocket && (serverConnection.isConnected === true) ){
        //interaction avec le serveur
    }else{
        Logger.log(Logger.error,"Serveur non connecté");
    }
};
    var stopTSP = function(){
    if (window.WebSocket && (serverConnection.isConnected === true) ){
        //interaction avec le serveur
    }else{
        Logger.log(Logger.error,"Serveur non connecté");
    }
};
    $('#play').click(playTSP);
    $('#pause').click(pauseTSP);
    $('#stop').click(stopTSP);
    
});