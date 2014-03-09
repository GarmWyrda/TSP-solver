define('environment', ['point'],function(Point){
    var Environment = {
        places : [],
        distanceMatrix : [],
        ways : [],
        clearWays : function(){
          for(var i=0;i<Environment.ways.length;i++){
              Environment.ways[i].hide();
          }
        },
        calculMatrix : function(){
            for (var i = 0; i < 30; i++) {
                var line = [];
                var Rayon = 6371000; // METRES
                for (var j = 0; j < 30; j++) {

                    var lat1 = Environment.places[i].lat;
                    var lon1 = Environment.places[i].lng;
                    var lat2 = Environment.places[j].lat;
                    var lon2 = Environment.places[j].lng;

                    //conversion en radian                  
                    var a = Math.PI / 180;
                    lat1 = (90 - lat1) * a;
                    lat2 = (90 - lat2) * a;
                    lon1 = lon1 * a;
                    lon2 = lon2 * a;

                    //conversion en coordonnées cartesiennes
                    var x1 = Rayon * Math.sin(lat1) * Math.cos(lon1);
                    var y1 = Rayon * Math.sin(lat1) * Math.sin(lon1);
                    var z1 = Rayon * Math.cos(lon1);

                    var x2 = Rayon * Math.sin(lat2) * Math.cos(lon2);
                    var y2 = Rayon * Math.sin(lat2) * Math.sin(lon2);
                    var z2 = Rayon * Math.cos(lon2);

                    //calcul de la distance
                    var distance = Math.sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
                    line.push(distance);
                }
                Environment.distanceMatrix.push(line);
            }
            console.log(Environment.distanceMatrix);
            Environment.printMatrix();
        },
        
        printMatrix : function() {
            var $zone = $('#matrix');
            var matrix = '<TABLE border=1>';
            for(var i=0;i<30;i++) {
                var line = '<TR>'; 
                for(var j=0;j<30;j++){
                    line += '<TD>' + Math.round(Environment.distanceMatrix[i][j]) +'</TD>';
                };
                line += '</TR>';
                matrix += line;   
            }
            matrix += '</TABLE>';
            $zone.html(matrix);
            console.log(matrix);
        }
    };
    
    $.getJSON('ressources/emplacements.txt', function(data) {
        for(var i=0;i<data.length;i++){
            Environment.places.push(new Point(data[i].lat,data[i].lng,data[i].id));
        }
    });
    
    return Environment;
});

