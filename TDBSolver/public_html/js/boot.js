// création des alias/paths
require.config({
    paths: {
        jquery: 'http://code.jquery.com/jquery-1.10.1.min.js',
        bootstrap : 'http://netdna.bootstrapcdn.com/bootstrap/3.1.0/js/bootstrap.min.js'
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


