/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('loadUI',['jQuery'],function(){
    $.getJSON("ressources/emplacements.txt",function(data){
       var length = data.length;
       var string = "";
       for(var i = 1;i<length+1;i++){
           string += "<option value=" + i + ">" + i + "</option> ";
       }
       $("#list").html(string);
    });
    $("#logger").append('<p class="alert-success">UI Loaded</p>');
});


