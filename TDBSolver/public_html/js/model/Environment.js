define('environment', ['map'],function(Map){
    var Environment = {
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

