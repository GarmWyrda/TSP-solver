define('environment', ['point','logger'],function(Point,Logger){
    var Environment = {
        places : [],
        distanceMatrix : [],
        ways : [],
        clearWays : function(){
          for(var i=0;i<Environment.ways.length;i++){
              Environment.ways[i].hide();
          }
        },
        calculMatrixFly : function(){
            if(Environment.distanceMatrix.length === 0){
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
            }
            Environment.printMatrix();
        },
        
        printMatrix : function() {
            var $zone = $('#matrix');
            $zone.html("");
            var matrix = '<TABLE border=1>';
            for(var i=0;i<Environment.distanceMatrix.length;i++) {
                var line = '<TR>'; 
                for(var j=0;j<Environment.distanceMatrix[i].length;j++){
                    line += '<TD>' + Math.round(Environment.distanceMatrix[i][j]) +'</TD>';
                };
                line += '</TR>';
                matrix += line;   
            }
            matrix += '</TABLE>';
            $zone.html(matrix);
        },
        
        printMatrixWalk:function(){
            var $zone = $('#matrix');
            $zone.html("");
            var distances = JSON.parse(localStorage.getItem("distanceMatrix"));
            var matrix = '<TABLE border=1>';
            for(var i=0;i<distances.length;i++) {
                var line = '<TR>'; 
                for(var j=0;j<distances[i].length;j++){
                    line += '<TD>' + distances[i][j] +'</TD>';
                };
                line += '</TR>';
                matrix += line;   
            }
            matrix += '</TABLE>';
            $zone.html(matrix);
        },
        
        calculMatrixWalk : function() {
            if(localStorage.getItem("distanceMatrix") === null){
                var places = [Environment.places[0].googlePoint,Environment.places[1].googlePoint,Environment.places[2].googlePoint];
                var service = new google.maps.DistanceMatrixService();
                service.getDistanceMatrix(
                    {
                        origins: places,
                        destinations: places,
                        travelMode: google.maps.TravelMode.WALKING,
                        unitSystem: google.maps.UnitSystem.METRIC,
                        durationInTraffic: false,
                        avoidHighways: false,
                        avoidTolls: false
                    }, function(response, status) {
                            if (status === google.maps.DistanceMatrixStatus.OK) {
                            var origins = response.originAddresses;
                            var destinations = response.destinationAddresses;
                            var matrix = [];
                            for (var i = 0; i < origins.length; i++) {
                                var line = [];
                                var results = response.rows[i].elements;
                                for (var j = 0; j < results.length; j++) {
                                    var element = results[j];
                                    var distance = element.distance.value;
                                    line.push(distance);

                                }
                                matrix.push(line);
                                //Environment.distanceMatrixWalk.push(line);
                            }
                            localStorage.setItem("distanceMatrix",JSON.stringify(matrix));
                            Environment.printMatrixWalk();
                            }
                        });
            }
            else{
                Environment.printMatrixWalk();
            }
        },
        clearCache : function(){
            if(localStorage.getItem("distanceMatrix") !== null){
                localStorage.removeItem("distanceMatrix");
                Logger.log(Logger.success,"Cache cleared");
            }
            else{
                Logger.log(Logger.error,"Cache already empty");
            }
        },
        
        fullMatrixWalking : function(){
            var part1 = [];
            var part2 = [];
            var part3 = [];
            var i=0;
            
            for(i=0;i<10;i++){
                part1.push(Environment.places[i].googlePoint);
            }
            
            for (i = 10; i < 20; i++) {
                part2.push(Environment.places[i].googlePoint);
            }
            
            for (i = 20; i < 30; i++) {
                part3.push(Environment.places[i].googlePoint);
            }
            
            var part = [part1, part2, part3];
            
            var matrix = [];
            
            for(var j=0;j<3;j++){
                for(var k=0;j<3;j++){
                    var service = new google.maps.DistanceMatrixService();
                    service.getDistanceMatrix(
                            {
                                origins: part[j],
                                destinations: part[k],
                                travelMode: google.maps.TravelMode.WALKING,
                                unitSystem: google.maps.UnitSystem.METRIC,
                                durationInTraffic: false,
                                avoidHighways: false,
                                avoidTolls: false
                            }, function(response, status) {
                        if (status === google.maps.DistanceMatrixStatus.OK) {
                            var origins = response.originAddresses;
                            var destinations = response.destinationAddresses;
                            for (var m = 0; m < origins.length; m++) {
                                //var line = [];
                                var results = response.rows[i].elements;
                                for (var n = 0; n < results.length; n++) {
                                    var element = results[j];
                                    var distance = element.distance.value;
                                    matrix[m+10*i].push(distance);

                                }
                                //Environment.distanceMatrixWalk.push(line);
                            }
                            localStorage.setItem("distanceMatrix", JSON.stringify(matrix));
                            Environment.printMatrixWalk();
                        }
                    });
                }
            }
            
        }
    };
    
    $.getJSON('ressources/emplacements.txt', function(data) {
        for(var i=0;i<data.length;i++){
            Environment.places.push(new Point(data[i].lat,data[i].lng,data[i].id));
        }
    });
    
    return Environment;
});

