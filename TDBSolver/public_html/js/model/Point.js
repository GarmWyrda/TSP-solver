define('point', ['jQuery','map','logger','GoogleMaps'],function($,Map,Logger,gmaps){
    var Point = function(lat,lng,id){
        this.lat = lat;
        this.lng = lng;
        this.googlePoint = google.maps.LatLng(lat,lng);
        this.marker = null;
    };
    return Point;
});

