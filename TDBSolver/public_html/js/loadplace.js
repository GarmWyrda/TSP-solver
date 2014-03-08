define('loadplace', ['jQuery','GoogleMaps','Logger'],function($, gmaps, Logger){
    var places = {
        list:[],
        marker:[],
        matrix:[]
    };

    var loadfile = function () {
        $.getJSON('ressources/emplacements.txt', function(data) {
            places.list = data;
        });
    };

    loadfile();
    
    var mapOptions = {
            zoom: 14,
            center: new google.maps.LatLng(50.631437, 3.061193)
        };
        
    var map = new google.maps.Map(document.getElementById("map"), mapOptions);
    
    var loadEmplacement = function(nb) {
        var id=0;
        var Lat=0;
        var Lng=0;
        for(var i=0;i<places.marker.length;i++){
            places.marker[i].setMap(null);
        }
        for(var i=0;i<nb;i++){
            id = places.list[i].id;
            Lat = places.list[i].lat;
            Lng = places.list[i].lng;
            places.marker[i] = new google.maps.Marker({
                position: new google.maps.LatLng(Lat, Lng),
                map: map,
                title: id,
                icon:'https://chart.googleapis.com/chart?chst=d_map_pin_letter&chld='+id+'|FF776B|000000'
            }); 
        } 
    };
    
    var printWay = function(A, B, byWalk) {

        var ptA = places.marker[A - 1].getPosition();
        var ptB = places.marker[B - 1].getPosition();
        
        if(byWalk == false){
            var extremites = [ptA,ptB];

            var flightWay = new google.maps.Polyline({
                path: extremites,
                geodesic: true,
                strokeColor: '#FF0000',
                strokeOpacity: 1.0,
                strokeWeight: 2,
                map: map
            });

            flightWay.setMap(map);
            Logger.log("alert-success","Way between " + A + "and" + B);
            
        }
        else {
            console.log("byWalk");
            var directionsService = new google.maps.DirectionsService();
            var directionsDisplay = new google.maps.DirectionsRenderer();
            var request = {
                origin: ptA,
                destination: ptB,
                travelMode: google.maps.DirectionsTravelMode.WALKING
            };
            directionsService.route(request, function(response, status) {
                if (status == google.maps.DirectionsStatus.OK) {
                    directionsDisplay.setDirections(response);
                }
            });
            directionsDisplay.setMap(map);
            $("#logger").append('<p class="alert-success">Way between ' + A + ' and ' + B + ' by walk traced</p>');
        }
    };
     
    $("#list").on("change",function(){
        console.log($("#list").val());
        loadEmplacement($("#list").val());
        
        //on adapte le contenu des listes pour tracer le chemin entre deux points
        var string = "";
        for (var i = 1; i <= $("#list").val(); i++) {
            string += "<option value=" + i + ">" + i + "</option> ";
        }
        $("#ptA").html(string);
        $("#ptB").html(string);
        
        $("#logger").append('<p class="alert-success">Marker(s) placed on the map</p>');
    });
        
    $("#validWay").on("click", function() {
        var A = $('#ptA').val();
        var B = $('#ptB').val();
        console.log("chemin entre " + A + " et " + B);
        
        var byWalk = $('#bywalk').is(':checked');
        printWay(A,B,byWalk);
        createMatrix(5);
        
    });
    
    var createMatrix = function(nb) {
        var points = [];
        console.log(places.list[0]);
        
        for(var i=0;i<nb;i++){
           var place = new google.maps.LatLng(places.list[i].lat, places.list[i].lng);
           points.push(place);
        }
        
        var service = new google.maps.DistanceMatrixService();
        service.getDistanceMatrix(
                {
                    origins: points,
                    destinations: points,
                    travelMode: google.maps.TravelMode.WALKING,
                    unitSystem: google.maps.UnitSystem.METRIC,
                    durationInTraffic: false,
                    avoidHighways: false,
                    avoidTolls: false
                }, callback);

        
        
        function callback(response, status) {
            console.log(response);
        }
    };
});