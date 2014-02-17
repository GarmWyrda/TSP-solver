// convert Google Maps into an AMD module
define('GoogleMaps', ['async!http://maps.google.com/maps/api/js?v=3&sensor=false'],
function(){
    return window.google.maps;
});
