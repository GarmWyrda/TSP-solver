// création des alias/paths
require.config({
    paths: {
        jquery: 'http://code.jquery.com/jquery-1.10.1.min.js',
        bootstrap : 'http://netdna.bootstrapcdn.com/bootstrap/3.1.0/js/bootstrap.min.js',
        googleApi : 'https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false',
        printMap : 'printmap.js'
    }
});
 
// module commun à tout le site
define('common', [
    'jquery'
], function($) {
    console.log('boot loaded');
});
 
// on charge le module commun
require(['common']);


