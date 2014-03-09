//CLASS UI
//Contient les méthodes relatives aux listeners, et a l'interface en général
define('ui',['listener','jQuery','logger','environment','map','way'],function(Listener,$,Logger,Environment,Map,Way){   
    var UI = {
        listeners : [],
        initialize : function(){
            this.listeners.push(new Listener($("#list"),"change",this.changePoints));
            this.listeners.push(new Listener($("#validWay"),"click",function(){
                var A = $('#ptA').val();
                var B = $('#ptB').val();
                var byWalk = $('#bywalk').is(':checked');
                if(A !== B){
                    var newWay = new Way(A,B,byWalk);
                    Environment.ways.push(newWay);
                }
            }));
            this.listeners.push(new Listener($("#getMatrixFly"), "click", Environment.calculMatrixFly));
            this.listeners.push(new Listener($("#getMatrixWalk"), "click", Environment.calculMatrixWalk));
            this.listeners.push(new Listener($("#clearWays"), "click", Environment.clearWays));
            for(var i = 0;i<UI.listeners.length;i++){
                UI.listeners[i].toggle();
            }
        },
        
        loadEmplacement : function(nb) {
            var id=0;
            var Lat=0;
            var Lng=0;
            for(var i=0;i<Environment.places.length;i++){
                Environment.places[i].marker.setVisible(false);
            }
            for(var i=0;i<nb;i++){
                Environment.places[i].marker.setVisible(true);
            } 
        },
        
       changePoints : function(){
            var $element = $("#list");
            UI.loadEmplacement($element.val());

            //on adapte le contenu des listes pour tracer le chemin entre deux points
            var string = "";
            for (var i = 1; i <= $element.val(); i++) {
                string += "<option value=" + i + ">" + i + "</option> ";
            }

            $("#ptA").html(string);
            $("#ptB").html(string);

            Logger.log(Logger.success,"Map changed");
        }
    };
    UI.initialize();
});
