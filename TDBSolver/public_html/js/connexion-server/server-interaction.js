define('server_interaction',['jQuery','logger','server_request'],function($,Logger,serverConnection){
    var etat = '';
    var way;
    var byWalk;
    var playTSP = function(){
        if (window.WebSocket && (serverConnection.isConnected === true) ){
            
            console.log($('#bywalk').val());
            if(($('#bywalk').val())==="true"){
                 way = 'distanceMatrix';
                 byWalk = true;
                 console.log('à pied');
            }else{
                 way = 'offRoad';
                 byWalk = false;
                console.log('oiseaux');
            }
        if(getGoodMatrix(way) === null ){
            return ;
        }else{
            var matrix = getGoodMatrix(way);
        }
        var request = {type : "play",matrix:matrix,size:$("#list").val(),byWalk:byWalk};
        serverConnection.socket.send(JSON.stringify(request));
            etat ='play';
            Logger.log(Logger.success,"play lancé");
        }else{
            Logger.log(Logger.error,"Serveur non connecté");
        }
    };
    
    var pauseTSP = function(){
    if (window.WebSocket && (serverConnection.isConnected === true) ){
        if(etat==='play'){
            var request = {type : "pause"};
            etat ='pause';
            serverConnection.socket.send(JSON.stringify(request));
            Logger.log(Logger.success,"pause envoyée");
        }else{
            Logger.log(Logger.error,"Plannification non lancée");
        };
    }else{
        Logger.log(Logger.error,"Serveur non connecté");
    }
};
    var stopTSP = function(){
    if (window.WebSocket && (serverConnection.isConnected === true) ){
        if(etat==='play'){
            var request = {type : "stop"};
            etat= 'stop';
            serverConnection.socket.send(JSON.stringify(request));
            Logger.log(Logger.success,"stop envoyée");
        }else{
            Logger.log(Logger.error,"Plannification non lancée");
        }
    }else{
        Logger.log(Logger.error,"Serveur non connecté");
    }
};


        getGoodMatrix = function(name) {
            if (localStorage.getItem(name) === null) {
              console.log(this);
              Logger.log(Logger.error,"matrice non présente dans le local storage");
              var matrix = null;
            }

            else {
                data = JSON.parse(localStorage.getItem(name));

                var $nbElement = $("#list");
                var matrix = new Array();
                for (var i = 0; i < [$nbElement.val()]; i++) {
                    matrix[i] = new Array();
                    for (var j = 0; j < [$nbElement.val()]; j++) {
                        console.log(i);
                        matrix[i][j] = parseInt(data[i][j]);
                    }
                }
                return (matrix);
            }
        };
        


    $('#play').click(playTSP);
    $('#pause').click(pauseTSP);
    $('#stop').click(stopTSP);
    
});
