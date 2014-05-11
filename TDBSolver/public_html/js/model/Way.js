define('way', ['jQuery','GoogleMaps','logger','environment','map'],function($, gmaps, Logger,Environment,Map){
   var Way = function(A,B,byWalk){ //Constructeur d'un chemin entre A et B, a pied ou non (byWalk)
       
       this.start = Environment.places[A - 1]; 
       
       this.stop = Environment.places[B - 1];
       
       this.createPolyline = function(){ //permet de cree la representation graphique du chemin
           if(byWalk === false){
                var extremites = [this.start.googlePoint,this.stop.googlePoint];
                var polyline = new google.maps.Polyline({
                    path: extremites,
                    geodesic: true,
                    strokeColor: '#FF0000',
                    strokeOpacity: 1.0,
                    strokeWeight: 2,
                    map: Map
                });
                        
                return polyline;
            }
            else {
                var directionsService = new google.maps.DirectionsService();
                //var directionsDisplay = new google.maps.DirectionsRenderer();
                var request = {
                    origin: this.start.googlePoint,
                    destination: this.stop.googlePoint,
                    travelMode: google.maps.DirectionsTravelMode.WALKING
                };
                directionsService.route(request, function(response, status) {
                    if (status === google.maps.DirectionsStatus.OK) {
                        
                        var data = response.routes[0].legs[0].steps;
                        var waypoints = [];
                        
                        for (var i=0; i<data.length; i++){
                            for (var j=0;j<data[i].path.length;j++) {
                                waypoints.push(data[i].path[j]);
                            }
                        }
                        
                        var polyline = new google.maps.Polyline({
                            path: waypoints,
                            geodesic: true,
                            strokeColor: '#0000FF',
                            strokeOpacity: 1.0,
                            strokeWeight: 2,
                            map: Map
                        });
                        
                        return polyline;
                    }
                });
          }
       };
       
       this.polyline = this.createPolyline();
       
       this.print = function(){ //Affiche la polyline(comportement par défaut)
           this.polyline.setVisible(true);
       };
       this.hide = function(){ //Cache la polyline
           this.polyline.setVisible(false);
       };
        Logger.log(Logger.success, "Way between " + A + " and " + B + "traced");
    };
    return Way;
});
