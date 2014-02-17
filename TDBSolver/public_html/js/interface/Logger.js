/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('logger',['jQuery'],function($){    
    /** Allow to send messages to the log area  */
        var Logger = {
        $zone : $("#logger"),/** define the area of the DOM which will be modified*/
        error : "alert-error",
        success : "alert-success",
        /** @constructor*/
        log : function(type,string){
            this.$zone.append("<p class = " + type + ">" + string + "</p>");/** Add the differents logs into the log area*/
        }             
    };
    
    return Logger; //**Singleton*/
});


