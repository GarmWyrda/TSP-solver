define('environment', ['map'],function(Map){
    var Environment = {
        map : Map,
        places : {
            points:[],
            markers:[]
        }
    };
    
    $.getJSON('ressources/emplacements.txt', function(data) {
        Environment.places.points = data;
    });
    
    return Environment;
});

