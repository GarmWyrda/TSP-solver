define('map', ['GoogleMaps','jQuery'],function(gmaps,$){
    var mapOptions = {
            zoom: 14,
            center: new google.maps.LatLng(50.631437, 3.061193)
        }; 
    var Map = new google.maps.Map(document.getElementById("map"),mapOptions); //Map graphique
    
    return Map;
});


