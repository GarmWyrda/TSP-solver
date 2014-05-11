define('environment', ['jQuery', 'point', 'distanceMatrix', 'logger'], function($, Point, Logger) {
    var Environment = {
        zoneMatrix: $('#matrix'),
        nb:0,
        places: [], //Emplacements
        ways: [], //Chemin tracés sur la carte

        matrixOffRoad: new Matrix("offRoad"),
        matrixByWalk: new Matrix("byWalk"),
        
        clearWays: function() { //Efface les chemins tracés sur la carte
            console.log(Environment.ways);
            for (var i = 0; i < Environment.ways.length; i++) {
                Environment.ways[i].hide();
            }
        },
                
        clearCache: function() { //Efface le localStorage
            if (localStorage.getItem("offRoad") !== null) {
                localStorage.removeItem("offRoad");
                Logger.log(Logger.success, "Distance matrix offRoad cleared");
            }
            if (localStorage.getItem("byWalk") !== null) {
                localStorage.removeItem("byWalk");
                Logger.log(Logger.success, "Distance matrix by walk cleared");
            }
            else {
                Logger.log(Logger.error, "Cache already empty");
            }
        },
                
        clearMatrix: function() { //Efface la matrice de la page
            $('#matrix').html('');
        }
    };

    //remplissage du tableau places de l'environnement
    $.getJSON("ressources/emplacements.txt")
            .done(function(data) {
        for (var i = 0; i < data.length; i++) {
            Environment.places.push(new Point(data[i].lat, data[i].lng, data[i].id));
        }
    }.bind(this))


            .fail(function(jqxhr, textStatus, error) {
        var err = "Request Failed: " + textStatus + ", " + error;
        console.log(err);
    });

    Math.toRad = function(Value) {
        /** Converts numeric degrees to radians */
        return Value * Math.PI / 180;
    };
    //surchage de la méthode calcul() sur l'instance "offRoad" du type Matrix
    Environment.matrixOffRoad.calcul = function() {
        var data = [];
        for (var i = 0; i < 30; i++) {
            var line = [];
            var R = 6371000; // METRES
            for (var j = 0; j < 30; j++) {
                var dLat = Math.toRad(Environment.places[j].lat - Environment.places[i].lat);
                var dLon = Math.toRad(Environment.places[j].lng - Environment.places[i].lng);
                var lat1 = Math.toRad(Environment.places[i].lat);
                var lat2 = Math.toRad(Environment.places[j].lat);

                var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) + Math.sin(dLon / 2) * Math.sin(dLon / 2) * Math.cos(lat1) * Math.cos(lat2);
                var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
                var dist = R * c;

                line.push(dist);
            }
            data.push(line);
        }
        localStorage.setItem(this.nameInStorage, JSON.stringify(data));
        this.print(Environment.zoneMatrix, Environment.nb);
    };

    //surchage de la méthode calcul() sur l'instance "byWalk" du type Matrix
    Environment.matrixByWalk.calcul = function() {
        alert("Please wait during the load");
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

        data = [];
        for (var c = 0; c < 30; c++) {
            data[c] = [];
        }

        for (var row = 0; row < 3; row++) {
            (function(currentRow) {
                for (var column = 0; column < 3; column++) {
                    (function(currentColumn) {
                        setTimeout(function() {
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
                                            data[10 * currentRow + i].push(distance);

                                        }
                                    }
                                    localStorage.setItem(Environment.matrixByWalk.nameInStorage, JSON.stringify(data));
                                    Environment.matrixByWalk.print(Environment.zoneMatrix, Environment.nb);
                                }
                            });
                        }, 10500 * (3 * currentRow + currentColumn));
                    })(column);
                }
            })(row);
        }
        ;
    };

    Environment.getMatrixOffRoad = function() {
        return Environment.matrixOffRoad.print(Environment.zoneMatrix, Environment.nb);
    };

    Environment.getMatrixByWalk = function() {
        return Environment.matrixByWalk.print(Environment.zoneMatrix, Environment.nb);
    };

    return Environment;
});

