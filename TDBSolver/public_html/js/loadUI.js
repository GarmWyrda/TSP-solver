/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('Logger',['jQuery'],function(){    
    var Logger = {
        $zone : $("#logger"),
        error : "alert-error",
        success : "alert-success",
        
        log : function(type,string){
            this.$zone.append("<p class = " + type + ">" + string + "</p>");
        }             
    };
    
    return Logger;

});


