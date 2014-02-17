/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('logger',['jQuery'],function($){    
    /** Load the differents elements of the map  */
        var Logger = {
        $zone : $("#logger"),
        error : "alert-error",
        success : "alert-success",
        /** @constructor*/
        log : function(type,string){
            this.$zone.append("<p class = " + type + ">" + string + "</p>");/** Add the differents logs into the log area*/
        }             
    };
    
    return Logger; //**Singleton*/
});


