define('map', ['GoogleMaps','jQuery'],function(gmaps,$){
    var Map = {
        mapOptions : {
            zoom: 14,
            center: new google.maps.LatLng(50.631437, 3.061193)
        },
        
        map : new google.maps.Map($("#map"), this.mapOptions)
    };
    
    return Map;
});


