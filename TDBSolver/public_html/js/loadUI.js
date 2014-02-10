/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
define('loadUI',['jQuery'],function(){
    console.log(string);
    $.getJSON("../ressources/emplacement.txt",function(data){
       var length = data.length;
       var string = "";
       for(var i = 1;i<length+1;i++){
           string += "<option value=" + i + ">" + i + "</option> ";
       }
       $("#list").html(string);
       console.log(string);
    });
});


