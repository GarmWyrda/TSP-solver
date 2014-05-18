define('server_request',['jQuery','logger','listener'],function($,Logger){
        // Objet connexion avec le serveur
        var serverConnection = { socket: undefined, isConnected: false, ip: "", port: -1 };
  
                    // Permet de se connecter ou de changer son pseudo
                    var connectWebSocket = function(ip, port) {
                            var host = 'ws://'+ip+':'+port;

                            if(!window.WebSocket) {
                                    alert('Votre navigateur ne supporte pas les webSocket !');
                                    return false;
                            } else {	
                                    // Nouvelle connexion
                                    if(serverConnection.isConnected) {
                                            serverConnection.socket.close();
                                    }
                                    // Création de la websocket
                                    serverConnection.ip = ip;
                                    serverConnection.port = port;

                                
                                    serverConnection.socket = new WebSocket(host);
                                    
                                    // Handler déclanché lors de l'ouverture de la websocket
                                    serverConnection.socket.onopen = function(event) {
                                            serverConnection.isConnected = true;
                                            $('#etat').html('<span class="info">Web Socket opened</span>');
                                            //serverConnection.socket.send($.toJSON(request));
                                    };

                                    // Handler déclanché lors de la fermeture de la websocket
                                    serverConnection.socket.onclose = function(event) {
                                            serverConnection.isConnected = false;
                                            $('#etat').html('<span class="error">Web Socket closed</span>');
                                    };

                                    // Handler déclanché lorsqu'une erreur
                                    serverConnection.socket.onerror = function(event) {
                                            serverConnection.isConnected = false;
                                            var error = "Impossible de se connecter au serveur ["+event.target.url+"]";
                                            Logger.log(Logger.error,error);
                                    };       
                                            // Handler déclanché dès qu'un nouveau message est envoyé au client
                                    serverConnection.socket.onmessage = function(event) {
                                        var msg = $.parseJSON(event.data);
                                        parseMessage(msg);
                                    };        
                                    function parseMessage(inMessage) {

                                            switch(inMessage.type) {
                                                case 'success':
                                                    Logger.log(Logger.success,inMessage.msg);
                                                     break;
                                                case 'little':
                                                    $('#cost').innerHTML(inMessage.cost);
                                                    $('#time').innerHTML(inMessage.time);
                                                    $('#type').innerHTML(inMessage.sol);
                                                    localStorage.setItem("points",inMessage.way);
                                                    for (var i = 0; i <way.length;i++){
                                                        var newWay = new Way(inMessage.way[i][0],inMessage.way[i][1], inMessage.byWalk);
                                                    }
                                                case 'error':
                                                    Logger.log(Logger.error,inMessage.msg);    
                                                    break;
                                                default:
                                                    return;
                                            }
                                        };
                                    }
                            };

                    // Vérifie que le formulaire de connexion est valide
                    var checkConnectionForm = function() {
                            var ip = $("#ip").val();
                            var port = $("#port").val();
                            var error = "";

                            if(!(port > 0 && port < 65536)) {
                                    error = "Port invalide";
                                    Logger.log(Logger.error,error);                                   
                            } else if(!/\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}/.test(ip)) {
                                    error = "IP invalide";
                                    Logger.log(Logger.error,error);
                            } else {
                                    // Si tout s'est bien passé, on peut se connecter
                                    connectWebSocket(ip, port);
                                    Logger.log(Logger.success,"IP et Port valides");
                            }
                    };
                    $('#connection').click(checkConnectionForm);
        return serverConnection;
});
