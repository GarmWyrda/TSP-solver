define('point', ['jQuery','map','logger','GoogleMaps'],function($,Map,Logger,gmaps){
    var Point = function(lat,lng,id){
        this.lat = lat;
        this.lng = lng;
        this.googlePoint = google.maps.LatLng(lat,lng);
        this.marker = new google.maps.Marker({
                    position: new google.maps.LatLng(lat, lng),
                    map: Map,
                    title: id,
                    icon:'https://chart.googleapis.com/chart?chst=d_map_pin_letter&chld='+id+'|FF776B|000000'
                }); 
        this.marker.setVisible(false);
    };
    return Point;
});

