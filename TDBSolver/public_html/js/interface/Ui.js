//CLASS UI
//Contient les méthodes relatives aux listeners, et a l'interface en général
define('ui',['listener','jQuery','logger','environment','map'],function(Listener,$,Logger,Environment,Map){   
    var UI = {
        listeners : [],
        initialize : function(){
            this.listeners.push(new Listener($("#list"),"change",this.changePoints));
            this.listeners.push(new Listener($("#validWay"),"click",function(){
                var A = $('#ptA').val();
                var B = $('#ptB').val();
                console.log("chemin entre " + A + " et " + B);
        
                var byWalk = $('#bywalk').is(':checked');
                printWay(A,B,byWalk);
            }));
            this.listeners[0].toggle();
            this.listeners[1].toggle();
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
            console.log($element.val());
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