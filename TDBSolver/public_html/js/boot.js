// création des alias/paths
require.config({
    paths: {
        jQuery: 'http://code.jquery.com/jquery-1.10.1.min',
        bootstrap : 'http://netdna.bootstrapcdn.com/bootstrap/3.1.0/js/bootstrap.min',
        googleApi : 'https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false',
        printMap : 'printMap'
    },
    shim: {
        'jQuery': {
            exports: 'jQuery'
        }                       
    }
});

require(["jQuery", "bootstrap","googleApi","printMap"], init);

function init() {
	
	console.log("Loading sucessful");

}
 

