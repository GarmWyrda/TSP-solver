define('way', ['jQuery','GoogleMaps','logger','environment','map'],function($, gmaps, Logger,Environment,Map){
   var Way = function(A,B){
       this.start = Environment.places[A - 1];
       this.stop = Environment.places[B - 1];
       this.polyline = null;
       this.print = function(byWalk) {
            
            if(byWalk === false){
                var extremites = [this.start.googlePoint,this.stop.googlePoint];
                var flightWay = new google.maps.Polyline({
                    path: extremites,
                    geodesic: true,
                    strokeColor: '#FF0000',
                    strokeOpacity: 1.0,
                    strokeWeight: 2,
                    map: Map
                });

                //flightWay.setMap(map);
                Logger.log(Logger.success,"Way between " + A + " and " + B);

            }
            else {
                var directionsService = new google.maps.DirectionsService();
                var directionsDisplay = new google.maps.DirectionsRenderer();
                var request = {
                    origin: this.start.googlePoint,
                    destination: this.stop.googlePoint,
                    travelMode: google.maps.DirectionsTravelMode.WALKING
                };
                directionsService.route(request, function(response, status) {
                    if (status === google.maps.DirectionsStatus.OK) {
                        directionsDisplay.setDirections(response);
                        console.log(response.routes[0]); 
                        
                        var walkedWay = new google.maps.Polyline({
                            path: response.routes[0].overview_path,
                            geodesic: true,
                            strokeColor: '#0000FF',
                            strokeOpacity: 1.0,
                            strokeWeight: 2,
                            map: Map
                        });
                        
                    }
                });
                Logger.log(Logger.success, "Way between " + A + " and " + B + " by walk traced");
        }
    };
    this.calculDist = function(byWalk) {
            if (byWalk === false){
                //calcul local
                var Rayon = 6371000; // METRES
                var lat1 = this.start.lat;
                var lon1 = this.start.lng;
                var lat2 = this.stop.lat;
                var lon2 = this.stop.lng;

                //conversion en radian                  
                var a = Math.PI / 180;
                lat1 = (90 - lat1) * a;
                lat2 = (90 - lat2) * a;
                lon1 = lon1 * a;
                lon2 = lon2 * a;

                //conversion en coordonnées cartesiennes
                var x1 = Rayon * Math.sin(lat1) * Math.cos(lon1);
                var y1 = Rayon * Math.sin(lat1) * Math.sin(lon1);
                var z1 = Rayon * Math.cos(lon1);

                var x2 = Rayon * Math.sin(lat2) * Math.cos(lon2);
                var y2 = Rayon * Math.sin(lat2) * Math.sin(lon2);
                var z2 = Rayon * Math.cos(lon2);

                //calcul de la distance
                var distance = Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
            }
            
            else {
                //requete google
            }
            
            return distance;
    };
   };
   
   return Way;
});
