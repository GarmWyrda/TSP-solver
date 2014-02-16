// création des alias/paths
require.config({
    paths: {
        jQuery: 'http://code.jquery.com/jquery-1.10.1.min',
        async: "../lib/async"
    },
    shim: {
        'jQuery': {
            exports: 'jQuery'
        }    
    }
});

require(["jQuery","GoogleMaps","printMap","loadUI","loadplace"], init);

function init() {	
	console.log("Loading sucessful");
}
 

