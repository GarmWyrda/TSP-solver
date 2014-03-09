define('environment', ['jQuery','point','logger'],function($,Point,Logger){
    var Environment = {
        places: [], //Emplacements
        distanceMatrix: [], //Matrice de distances a vol d'oiseau
        ways: [], //Chemin tracés sur la carte
   
        clearWays: function() { //Efface les chemins tracés sur la carte
            for (var i = 0; i < Environment.ways.length; i++) {
                Environment.ways[i].hide();
            }
        },
        
        calculMatrixFly: function() { //Calcule et affiche la matrice de distances a vol d'oiseau
            if (Environment.distanceMatrix.length === 0) {
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
            Environment.printMatrix(); //Affichage de la matrice dans le DOM
        },
        
        printMatrix: function() { //Affiche la matrice de distance à vol d'oiseau de la classe Environment
            var $zone = $('#matrix');
            $zone.html("");
            var matrix = '<TABLE border=1>';
            for (var i = 0; i < Environment.distanceMatrix.length; i++) {
                var line = '<TR>';
                for (var j = 0; j < Environment.distanceMatrix[i].length; j++) {
                    line += '<TD>' + Math.round(Environment.distanceMatrix[i][j]) + '</TD>';
                }
                ;
                line += '</TR>';
                matrix += line;
            }
            matrix += '</TABLE>';
            $zone.html(matrix);
        },
        
        printMatrixWalk: function() { //Affiche la matrice de distances a pied du localStorage
            var $zone = $('#matrix');
            $zone.html("");
            var distances = JSON.parse(localStorage.getItem("distanceMatrix"));
            var matrix = '<TABLE border=1>';
            for (var i = 0; i < distances.length; i++) {
                var line = '<TR>';
                for (var j = 0; j < distances[i].length; j++) {
                    line += '<TD>' + distances[i][j] + '</TD>';
                }
                ;
                line += '</TR>';
                matrix += line;
            }
            matrix += '</TABLE>';
            $zone.html(matrix);
        },
        
        clearCache: function() { //Efface le localStorage
            if (localStorage.getItem("distanceMatrix") !== null) {
                localStorage.removeItem("distanceMatrix");
                Logger.log(Logger.success, "Cache cleared");
            }
            else {
                Logger.log(Logger.error, "Cache already empty");
            }
        },
        
        fullMatrixWalking: function() { //Calcule la matrice complete des distances a pied
    //la stocke dans le localStorage une fois fini et l'affiche au fur et a mesure
            if (localStorage.getItem("distanceMatrix") === null){
                var part1 = [];
                var part2 = [];
                var part3 = [];
                var i = 0;

                for (i = 0; i < 10; i++) {
                    part1.push(Environment.places[i].googlePoint);
                }

                for (i = 10; i < 20; i++) {
                    part2.push(Environment.places[i].googlePoint);
                }

                for (i = 20; i < 30; i++) {
                    part3.push(Environment.places[i].googlePoint);
                }

                var part = [part1, part2, part3];

                Environment.matrix = [];
                for(var c=0;c<30;c++){
                    Environment.matrix[c] = [];
                }

                for(var row=0;row<3;row++){
                    (function(currentRow) {
                        for(var column = 0; column<3;column++){
                            (function(currentColumn) {
                                setTimeout(function(){
                                    var service = new google.maps.DistanceMatrixService();
                                    service.getDistanceMatrix(
                                            {
                                                origins: part[currentRow],
                                                destinations: part[currentColumn],
                                                travelMode: google.maps.TravelMode.WALKING,
                                                unitSystem: google.maps.UnitSystem.METRIC,
                                                durationInTraffic: false,
                                                avoidHighways: false,
                                                avoidTolls: false
                                            }, function(response, status) {
                                        if (status === google.maps.DistanceMatrixStatus.OK) {
                                            var origins = response.originAddresses;
                                            var destinations = response.destinationAddresses;
                                            for (var i = 0; i < origins.length; i++) {

                                                var results = response.rows[i].elements;
                                                for (var j = 0; j < results.length; j++) {
                                                    var element = results[j];
                                                    var distance = element.distance.value;
                                                    Environment.matrix[10*currentRow+i].push(distance);
                                                    
                                                }                                           
                                            }
                                            localStorage.setItem("distanceMatrix", JSON.stringify(Environment.matrix));
                                            Environment.printMatrixWalk();
                                        }
                                    });
                                },10500*(3*currentRow+currentColumn));
                             })(column);
                         }
                    })(row);
                }
            }
            else{
                Environment.printMatrixWalk();
            }
        },
        clearMatrix : function(){ //Efface la matrice de la page
            $('#matrix').html('');
        }
    };

    $.getJSON('ressources/emplacements.txt', function(data) { //On récupére la liste d'emplacement pour la sauvegarder dans
        //Environment.places
        for (var i = 0; i < data.length; i++) {
            Environment.places.push(new Point(data[i].lat, data[i].lng, data[i].id));
        }
    });

    return Environment;
});

