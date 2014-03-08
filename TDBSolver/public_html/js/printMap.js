    define('printMap', 
['GoogleMaps'],function(){
    var mapOptions = {
        zoom: 16,
        center: new google.maps.LatLng(50.634327, 3.048550)
    };
    
    var map = new google.maps.Map(document.getElementById("map"),mapOptions);
    
    var isen = new google.maps.Marker({
        position: new google.maps.LatLng(50.634327, 3.048550),
        map: map,
        title: 'ISEN'
    }); 
});


