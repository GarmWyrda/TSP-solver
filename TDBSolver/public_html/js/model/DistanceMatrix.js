define('distanceMatrix', ['jQuery', 'map', 'logger', 'environment', 'GoogleMaps'], function($, Map, Logger, gmaps) {
    Matrix = function(name) {
        this.nameInStorage = name,
        this.print = function(zone, nb) {
            if (localStorage.getItem(this.nameInStorage) === null) {
              console.log(this);
              this.calcul();
            }

            else {
                data = JSON.parse(localStorage.getItem(this.nameInStorage));

                zone.html("");
                var matrix = '<TABLE><TH></TH>';

                for (var i = 1; i <= nb; i++) {
                    matrix += '<TH>' + i + '</TH>';
                };

                for (var i = 0; i < nb; i++) {
                    var nbLine = i + 1;
                    var line = '<TR><TH>' + nbLine + '</TH>';
                    for (var j = 0; j < nb; j++) {
                        line += '<TD>' + Math.round(data[i][j]) + '</TD>';
                    }
                    ;
                    line += '</TR>';
                    matrix += line;
                }
                matrix += '</TABLE>';
                zone.html(matrix);
            }
            ;
        };
    }; 
});





