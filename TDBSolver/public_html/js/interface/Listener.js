/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('listener',['jQuery'],function($){
    var Listener = function(elementHTML,event,callback) {
        this.elementHTML = elementHTML;
        this.event = event;
        this.callback = callback;
        this.isOn = false;
        this.trigger = function(){
            if(this.isOn){
                $(this.elementHTML).off();
            }
            else{
                $(this.elementHTML).on(event,callback);
            }
        };
    };
    
    return Listener;
});

