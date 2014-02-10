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
    
    $("#list").on("change",function(){
        console.log($("#list").val());
        loadEmplacement($("#list").val());
        $("#logger").append('<p class="alert-success">Map changed</p>');
    });
});