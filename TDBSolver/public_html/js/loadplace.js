define('loadplace', ['jQuery','GoogleMaps'],function(){
    var places = {
        list:[],
        marker:[]
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
    
    var printWay = function(A, B) {

        var LatA = places.list[A - 1].lat;
        var LngA = places.list[A - 1].lng;

        var LatB = places.list[B - 1].lat;
        var LngB = places.list[B - 1].lng;

        var extremites = [
            new google.maps.LatLng(LatA, LngA),
            new google.maps.LatLng(LatB, LngB)
        ];

        var flightWay = new google.maps.Polyline({
            path: extremites,
            geodesic: true,
            strokeColor: '#FF0000',
            strokeOpacity: 1.0,
            strokeWeight: 2,
            map: map
        });

        flightWay.setMap(map);
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
        
        printWay(A,B);
        
        $("#logger").append('<p class="alert-success">Way between ' + A + 'and ' + B + 'traced</p>');
    });
});

