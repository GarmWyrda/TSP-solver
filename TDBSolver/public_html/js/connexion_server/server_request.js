define('server_request',['jQuery','logger'],function($){
$(function() {
        // Objet connexion avec le serveur
        var serverConnection = { socket: undefined, isConnected: false, ip: "", port: -1, pseudo: "" }

        // Tous les messages reçu via la websocket passe par cette fonction
        function parseMessage(inMessage) {
                var scrollTop = $("#chat").scrollTop();
                var height = $("#chat").height();
                var scrollHeight = $("#chat").prop('scrollHeight');
                var autoScroll = false;
                if(10 == scrollHeight-scrollTop-height) {
                        autoScroll = true;
                }

        switch(inMessage.type) {
            case 'msg':
                $('#chat ul').append('<li><span class="bold">'+inMessage.params.pseudo+' : </span><span class="msg">'+inMessage.params.msg+'</span></li>');
                break;
            case 'info':
                $('#chat ul').append('<li><span class="info">'+inMessage.params.msg+'</span></li>');
                break;
                                    case 'error':
                $('#chat ul').append('<li><span class="error"><span class="bold">Erreur : </span>'+inMessage.params.msg+'</span></li>');
                break;
            case 'history':
                for(var i = 0; i < inMessage.params.data.length; ++i) { parseMessage(inMessage.params.data[i]); }
                break;
                                    case 'user-list':
                                            $("#user-list ul").html("");
                for(var i = 0; i < inMessage.params.users.length; ++i) { $("#user-list ul").append('<li>'+inMessage.params.users[i]+'</li>'); }
                break;
            default:
                                            return;
        }

                            if(autoScroll) { $("#chat").scrollTop($("#chat").prop('scrollHeight')) }
    }

                    // Permet de se connecter ou de changer son pseudo
                    var connectWebSocket = function(ip, port, pseudo) {
                            var host = 'ws://'+ip+':'+port;

                            if(!window.WebSocket) {
                                    alert('Votre navigateur ne supporte pas les webSocket !');
                                    return false;
                            } else if(serverConnection.isConnected && serverConnection.ip == ip && serverConnection.port == port) {
                                    // Changement de pseudo
                                    var request = { type:"changePseudo", params:{ pseudo:$('#pseudo').val() } };
                                    serverConnection.socket.send($.toJSON(request));
                            } else {	
                                    // Nouvelle connexion
                                    if(serverConnection.isConnected) {
                                            serverConnection.socket.close();
                                    }
                                    // Création de la websocket
                                    serverConnection.ip = ip;
                                    serverConnection.port = port;
                                    serverConnection.pseudo = pseudo;

                                    for(var i=0; i< 1; i++){
                                            serverConnection.socket = new WebSocket(host);
                                    }

                                    // Handler déclanché dès qu'un nouveau message est envoyé au client
                                    serverConnection.socket.onmessage = function(event) {
                    var msg = $.parseJSON(event.data);
                    parseMessage(msg);
                                    }

                                    // Handler déclanché lors de l'ouverture de la websocket
                                    serverConnection.socket.onopen = function(event) {
                                            serverConnection.isConnected = true;
                                            $('#etat').html('<span class="info">Web Socket opened</span>');
                                            var request = { type:"changePseudo", params:{ pseudo:$('#pseudo').val() } };
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
                    }

                    // Vérifie que le formulaire de connexion est valide
                    var checkConnectionForm = function() {
                            var ip = $("#ip").val();
                            var port = $("#port").val();
                            var pseudo = $.trim($("#pseudo").val());

                            var error = { type:"error", params:{ msg:"" } };

                            if(!pseudo || 0 === pseudo.length) {
                                    error.params.msg = "Pseudo invalide";
                                    parseMessage(error);
                            } else if(!(port > 0 && port < 65536)) {
                                    error.params.msg = "Port invalide";
                                    parseMessage(error);
                            } else if(!/\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}/.test(ip)) {
                                    error.params.msg = "IP invalide";
                                    parseMessage(error);
                            } else {
                                    // Si tout s'est bien passé, on peut se connecter
                                    connectWebSocket(ip, port, pseudo);
                            }
                    }
                    $('#connection').click(checkConnectionForm);

                    // Envoi d'un message aux autres clients
                    var sendMessage = function() {
                            if($('#msg').val() === '') { return; }
                            // Envoi d'une requête au serveur
        console.log("Sending message");
        var request = { type:"send", params:{ msg:$('#msg').val() } };
                            serverConnection.socket.send($.toJSON(request));
                            $('#msg').val('');
                    };
                    $('#send').click(sendMessage);

                    // Bind de la touche ENTER avec l'envoi du message
                    $('#msg').keyup(function(event) { if(13 === event.which) { sendMessage(); event.preventDefault(); } });
                    // Bind de la touche ENTER avec le formulaire de connexion
                    $('#ip').keyup(function(event) { if(13 === event.which) { $('#port').focus(); event.preventDefault(); } });
                    $('#port').keyup(function(event) { if(13 === event.which) { $('#pseudo').focus(); event.preventDefault(); } });
                    $('#pseudo').keyup(function(event) { if(13 === event.which) { checkConnectionForm(); event.preventDefault(); } });

                    // Redimentionnement automatique de la page
                    function autoHeight(){ var h_window = $(window).height()-192; $('#chat').css('height', h_window); $('#user-list').css('height', h_window); }				
                    // Redimentionnement de l'apply au chargement et après un redimentionnement de la fenêtre
                    $(window).resize(function(){ autoHeight(); });			
                    $(window).load(function(){ autoHeight(); });    
})
