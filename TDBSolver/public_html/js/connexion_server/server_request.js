define('server_request',['jQuery','logger'],function($){
        // Objet connexion avec le serveur
        var serverConnection = { socket: undefined, isConnected: false, ip: "", port: -1, pseudo: "" };
  
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

                                    for(var i=0; i< 1; i++){
                                            serverConnection.socket = new WebSocket(host);
                                    }
                                    // Handler déclanché lors de l'ouverture de la websocket
                                    serverConnection.socket.onopen = function(event) {
                                            serverConnection.isConnected = true;
                                            $('#etat').html('<span class="info">Web Socket opened</span>');
                                            serverConnection.socket.send($.toJSON(request));
                                    };

                                    // Handler déclanché lors de la fermeture de la websocket
                                    serverConnection.socket.onclose = function(event) {
                                            serverConnection.isConnected = false;
                                            $('#etat').html('<span class="error">Web Socket closed</span>');
                                    };

                                    // Handler déclanché lorsqu'une erreur
                                    serverConnection.socket.onerror = function(event) {
                                            serverConnection.isConnected = false;
                                            var error = { type:"error", params:{ msg:"Impossible de se connecter au serveur ["+event.target.url+"]" } };
                                            parseMessage(error);
                                    };
                            }
                    };

                    // Vérifie que le formulaire de connexion est valide
                    var checkConnectionForm = function() {
                            var ip = $("#ip").val();
                            var port = $("#port").val();
                            var error = { type:"error", params:{ msg:"" } };

                            if(!(port > 0 && port < 65536)) {
                                    error.params.msg = "Port invalide";
                                    parseMessage(error);
                                    console.log("pfd");
                            } else if(!/\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}/.test(ip)) {
                                    error.params.msg = "IP invalide";
                                    parseMessage(error);
                                    console.log("pfd toussa");
                            } else {
                                    // Si tout s'est bien passé, on peut se connecter
                                    connectWebSocket(ip, port, pseudo);
                                    console.log("ba alors");
                            }
                    };
                    $('#connection').click(checkConnectionForm);
 
});
