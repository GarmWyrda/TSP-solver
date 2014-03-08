//CLASS UI
//Contient les méthodes relatives aux listeners, et a l'interface en général
define('ui',['listener','jQuery','logger','environment'],function(Listener,$,Logger,Environment){   
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
            for(var i=0;i<Environment.places.markers.length;i++){
                Environment.places.markers[i].setMap(null);
            }
            for(var i=0;i<nb;i++){
                id = Environment.places.points[i].id;
                Lat = Environment.places.points[i].lat;
                Lng = Environment.places.points[i].lng;
                Environment.places.markers[i] = new google.maps.Marker({
                    position: new google.maps.LatLng(Lat, Lng),
                    map: Map.map,
                    title: id,
                    icon:'https://chart.googleapis.com/chart?chst=d_map_pin_letter&chld='+id+'|FF776B|000000'
                }); 
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