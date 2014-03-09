define('listener',['jQuery'],function($){ //Class Listener
    var Listener = function(elementHTML,event,callback) { //Constructeur 
        this.elementHTML = elementHTML; //Zone a ecoute
        this.event = event; //Evenement a ecouter
        this.callback = callback; //Fonction a appeler lorsque l'evenement est lance
        this.isOn = false; //Etat du listener
        this.toggle = function(){ //Allume/eteint le listener
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

