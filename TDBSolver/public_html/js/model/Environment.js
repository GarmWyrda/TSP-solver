define('environment', ['point'],function(Point){
    var Environment = {
        places : []
    };
    
    $.getJSON('ressources/emplacements.txt', function(data) {
        for(var i=0;i<data.length;i++){
            Environment.places.push(new Point(data[i].lat,data[i].lng,data[i].id));
        }
    });
    
    return Environment;
});

