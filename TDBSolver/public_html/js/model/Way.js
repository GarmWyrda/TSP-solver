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

                flightWay.setMap(map);
                Logger.log(Logger.success,"Way between " + A + "and" + B);

            }
            else {
                var directionsService = new google.maps.DirectionsService();
                var directionsDisplay = new google.maps.DirectionsRenderer();
                var request = {
                    origin: ptA,
                    destination: ptB,
                    travelMode: google.maps.DirectionsTravelMode.WALKING
                };
                directionsService.route(request, function(response, status) {
                    if (status === google.maps.DirectionsStatus.OK) {
                        directionsDisplay.setDirections(response);
                    }
                });
                directionsDisplay.setMap(map);
                Logger.log(Logger.success,"Way between ' + A + ' and ' + B + ' by walk traced");
        }
    };
   };
   return Way;
});
