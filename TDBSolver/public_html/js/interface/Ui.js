/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


define('ui',['listener'],function(){
    var UI = {
        initialize : function(){
            this.listeners.push(Listener());
        },
        listeners : []
        
    };
    
    return UI;
});