define('logger',['jQuery'],function($){    
    /** Allow to send messages to the log area  */
    var Logger = { //Class Logger, permet d'envoyer des messages dans la zone de log
        $zone : $("#logger"),/** define the area of the DOM which will be modified*/
        error : "error", //CSS d'erreur
        success : "alert-success", //CSS de succes
        /** @constructor*/
        log : function(type,string){ //Affiche string dans la zone de log avec le CSS type
            this.$zone.append("<p class = " + type + ">" + string + "</p>");/** Add the differents logs into the log area*/
        }             
    };
    
    return Logger; //**Singleton**//
});


