#include "Matrix/matrix.h"
#include "Little/Little.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "tspParse.h"
#include <sstream>
#include <string>

// STL containers
#include <map>
#include <set>

// websocket++
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

// JSON parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// boost threads
#include <boost/thread.hpp>


typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::lib::function;

using namespace boost::property_tree;
using namespace std;


class Clock
{
    private:

    boost::thread* pThread; // The thread runs this object
    bool mustStop;
    int step;
    boost::function< void (int) > callBack;

    
    public:

    Clock(boost::function< void (int) > callBack)
    {
        this->step = 0;
        this->pThread = NULL;
        this->mustStop = true;
        this->callBack = callBack;
    }
    
    void start(){
        this->mustStop = false;
        pThread = new boost::thread(boost::ref(*this));        
    }
    
    // Stop the thread
    void stop()
    {
        mustStop = true;

        // Wait for the thread to finish.
        //if (pThread != NULL) pThread->join();
    }    


    void operator() ()
    {
        

        while (!mustStop){

            callBack(step);
            
            sleep(1);

            step++;

        }
        
    }
    
    ~Clock()
    {
        delete pThread;
    }

};

class Message{  // abstract class
    private:
    string content;   

    public:
    Message(string content){
        this->content = content;
    }   
    
    string getContent(){
        return content;
    }
    
    // string representation to be printed
    virtual string toString() = 0;

    // JSON representation
    virtual string toJSON() = 0;    
    
};

class ClientMessage : public Message{   

    private:
    string pseudo;
    
    public:
 
    ClientMessage(string msg, string pseudo) : Message(msg){
        this->pseudo = pseudo;
    }

    string getPseudo(){
        return pseudo;
    }

    // @Overrides Message::toString()
    string toString(){
            stringstream s;
            s << "pseudo: " << pseudo << endl; 
            s << "msg: " << getContent() << endl; 
            return s.str();
    }

    // @Overrides Message::toJSON()
    string toJSON(){

        stringstream s;

        s << "{\"type\":\"msg\",\"params\":{\"msg\":\"";
        s << getContent() << "\",";
        s << "\"pseudo\":\"";
        s << pseudo << "\"";
        s << "}}";    

        return s.str();
    }
};


class InfoMessage : public Message{
    
    public:

    InfoMessage(string infoMsg) : Message(infoMsg) {}
    
    
    // @Overrides Message::toString()
    string toString(){
            stringstream s;
            s << "info: " << getContent() << endl; 
            return s.str();
    }    
    
    // @Overrides Message::toJSON()
    string toJSON(){

        stringstream s;

        s << "{\"type\":\"info\",\"params\":{\"msg\":\"";
        s << getContent() << "\"}}";    

        return s.str();
    } 

};

class ErrorMessage : public Message{
    
    public:

    ErrorMessage(string errorMsg) : Message(errorMsg) {}
    
    
    // @Overrides Message::toString()
    string toString(){
            stringstream s;
            s << "error: " << getContent() << endl; 
            return s.str();
    }   
    
    // @Overrides Message::toJSON()
    string toJSON(){

        stringstream s;

        s << "{\"type\":\"error\",\"params\":{\"msg\":\"";
        s << getContent() << "\"}}";    

        return s.str();

    } 
};


class Logger{
	
    public:

    static ostream& log(ostream& os, string message){
        time_t t = time(NULL);
        tm* lt = localtime(&t);	
        char buffer[20];

        strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S",lt);
        return os << "[" << buffer << "] " << message << endl;
    }
};



class Client {
	
    private:
    server::connection_ptr pConnection;
    string pseudo;

    public:	
    Client(server::connection_ptr pConnection){

        this->pConnection = pConnection;		
        this->pseudo = "";      // convention : empty pseudo until a "changePseudo" msg is sent

    }

    string toString(){
        stringstream s;
        s << "pseudo: " << pseudo << endl; 
        s << "remote endpoint: " << pConnection->get_remote_endpoint() << endl; 
        s << "user agent: " << pConnection->get_request_header("User-Agent") << endl;
        return s.str();
    }

    string getPseudo(){
        return pseudo;
    }
    
    void setPseudo(string pseudo){
        this->pseudo = pseudo;
    }        

    string getId(){
        stringstream s;
        s << pseudo << "@" << pConnection->get_remote_endpoint();
        return s.str();		
    }

    server::connection_ptr getConnection(){
        return pConnection;
    }
		
};


class UserList{
    
    private:
    set<string> users;
        
    public:

    void add(string user){
        users.insert(user);
    }
    
    void remove(string user){
        users.erase(user);
    }
    
    bool contains(string user){
        return (users.count(user) > 0);
    }
    
    
    string toJSON(){

        stringstream s;

        s << "{\"type\":\"user-list\",\"params\":{\"users\":[";
        
        int nbPseudos = users.size();
        int pseudoCpt = 0;
        
        for (set<string>::iterator pseudoIterator = users.begin(); pseudoIterator != users.end(); ++pseudoIterator){
            
            pseudoCpt++;
            s << "\"" << *pseudoIterator << "\"";
            
            if(pseudoCpt != nbPseudos){
               s << ","; 
            }
        }
          
        
        s << "]}}";    

        return s.str();
    } 
};


class ChatServer {
	
    private:

    // fields
    Clock clock;
    server embbeddedServer;
    map<connection_hdl, Client*> clients;
    UserList userList;
    
    // methods
    
    void onClockTick(int step){

        
        stringstream s;
        s << step;
        
        ClientMessage* stepMessage = new ClientMessage(s.str(), "clock");
        fireMessage( stepMessage->toJSON() );
        
        delete stepMessage;
        
    }
    // called when a new connection is established
    void onOpen(connection_hdl hdl) {

        
        Client* pClient = new Client(embbeddedServer.get_con_from_hdl(hdl));
        
        clients[ hdl ] = pClient;
        
        stringstream logStream;
        logStream << "New client connected." << endl;
        logStream << pClient->toString();
        logStream << "Number of connected clients: " << clients.size() << endl;
        
    
		
        Logger::log(cout, logStream.str() );
 
    }  
    
    // called when a connection is closed
    void onClose(connection_hdl hdl) {

        Client* pClient = clients[ hdl ];	// retrieving client

        
        clients.erase( hdl );	// removing client from the map
        
        string pseudo = pClient->getPseudo();
        if(!pseudo.empty()){
            
            userList.remove( pseudo );  // removing client pseudos from userList
            
            stringstream logStream;
            logStream << "Client " << pClient->getId() << " disconnected." << endl;
            logStream << "Number of connected clients: " << clients.size() << endl;

            stringstream infoStream;
            infoStream << pseudo << " left the chat";

            InfoMessage* infoMsg = new InfoMessage( infoStream.str() );
            string infoJSON = infoMsg->toJSON();


            fireMessage(logStream, infoJSON, true);   
            
            delete infoMsg;

            Logger::log(cout, logStream.str() );
        }
        
        delete pClient; // deallocating client
                
    }


    
    // called on incoming message
    void onMessage(connection_hdl hdl, server::message_ptr msg) {
 
        
        Client* pClient = clients[ hdl ];	// retrieving client

        string receivedString =  msg->get_payload();
        


        stringstream logStream;
        logStream << "Received message from client " << pClient->getId() << ":" << endl;
        logStream << receivedString << endl;
        
        Message* pMessage = processJSON(receivedString, pClient);

        if(pMessage == NULL){
            logStream << "Ill formed message -> not broadcasted " << endl;
        }
        else{
            logStream << "Parsed object: " << endl;
            logStream << pMessage->toString();

            string msgJSON = pMessage->toJSON();        // polymorphic behavior

    
  
            if(NULL != dynamic_cast<ErrorMessage*>(pMessage)){
                
                logStream << "Sending back to client error message : " << endl;

                logStream << msgJSON << endl;
                
                pClient->getConnection()->send(msgJSON); // error msg to the pClient only
                
                if( pClient->getPseudo().empty() ){     // no valid pseudo : the client cannot stay in the chat room
     
                    pClient->getConnection()->close(websocketpp::close::status::invalid_payload, pMessage->getContent() );   // closing connection

                }
            }
            else{
  
                fireMessage(logStream, msgJSON, NULL == dynamic_cast<ClientMessage*>(pMessage));   // pClient's msg to all clients             
                
            }

        }

        Logger::log(cout, logStream.str() );

        delete pMessage;
    }
    
    // returns NULL on problem
    Message* processJSON(string json, Client* pClient){

        stringstream s;
        s << json;

        ptree pt;
        read_json(s, pt);
        
        string pseudo = pClient->getPseudo();

        try{
            string type = pt.get_child("type").data();

            if(type == "send"){

                string msg = pt.get_child("params.msg").data();

                if( !msg.empty() ){
                    
                    if(msg == "startClock"){    // partie ad hoc pour illustrer le fonctionnement d'un thread
                        clock.start();
                        return new InfoMessage("clock started");
                    }
                    else if(msg == "stopClock"){
                        clock.stop();
                        return new InfoMessage("clock stopped");
                    }
                    else {
                        return new ClientMessage(msg, pseudo);
                    }
                }
            }
            else if(type == "changePseudo"){
                
                
                string newPseudo = pt.get_child("params.pseudo").data();

                if( !newPseudo.empty() ){
                    
                    if( !userList.contains(newPseudo) ){ // requested pseudo unused -> OK
                        stringstream infoStream;
                    
                        if(pseudo.empty()){     // initial pseudo setting

                            infoStream << newPseudo << " joined the chat ";
                            infoStream << "(remote endpoint: " << pClient->getConnection()->get_remote_endpoint() << ")"; 
     
                        }
                        else{   // pseudo change
                            
                            infoStream << pseudo << " changed his pseudo to " << newPseudo;
                            userList.remove(pseudo);
                            
                        }
                        
                        
                    
                        userList.add(newPseudo); // insert new pseudo in used pseudos
                        pClient->setPseudo(newPseudo); // change the client's pseudo
                        
                        return new InfoMessage(infoStream.str());                        
                    }
                    else if(newPseudo != pseudo){       // if the same pseudo is resubmitted, no error is sent

                        stringstream errorStream;
                        
                        errorStream << "the pseudo " << newPseudo << " is already used ";
                    
                        return new ErrorMessage(errorStream.str());                         
                        
                    }
                    
    
                }                
                
            }
        }
        catch(...){
            // nothing to do
        }

        return NULL;


    }      
    
    // sends the specified json message + the updated user list if asked
    void fireMessage(stringstream& logStream, string msgJSON, bool fireUserList){
        
        
        logStream << "Sending to all connected clients: " << endl;
        logStream << msgJSON << endl;
                
        fireMessage(msgJSON);

        string userListJSON;
        
        if(fireUserList){
            
            userListJSON = userList.toJSON();
            logStream << userListJSON << endl;
            fireMessage(userListJSON);
        }
        
        

         
    }   
    
    
        // sends the specified json message + the updated user list if asked
    void fireMessage(string msgJSON){  
        
        for(map<connection_hdl, Client*>::iterator clientIterator = clients.begin(); clientIterator != clients.end(); ++clientIterator) {

            clientIterator->second->getConnection()->send(msgJSON);
        }        
        
    }  

    public:
    ChatServer() : clock( bind( &ChatServer::onClockTick, this,::_1 ) ){
        
        embbeddedServer.init_asio();

        // disable default loggers
        embbeddedServer.clear_access_channels(websocketpp::log::alevel::all);
        embbeddedServer.clear_error_channels(websocketpp::log::alevel::all);

        embbeddedServer.set_open_handler(bind(&ChatServer::onOpen,this,::_1));
        embbeddedServer.set_close_handler(bind(&ChatServer::onClose,this,::_1));
        embbeddedServer.set_message_handler(bind(&ChatServer::onMessage,this,::_1,::_2));
    }


    void run(int port) {
        
        embbeddedServer.listen(port);
        embbeddedServer.start_accept();
        
        stringstream logStream;
        logStream << "Chat server running." << endl;
        logStream << "Listening to port " << port << endl;

		
        Logger::log(cout, logStream.str() );
        embbeddedServer.run();
    }


};





int main(int argc, char** argv) {

    int port = 0;
    
    if(argc > 1){
        port = atoi(argv[1]);
    }
	
    if(port == 0){
        cerr << "unable to determine port" << endl;
        return EXIT_FAILURE;
    }
	
	
    ChatServer server;
    server.run(port);
}

int main1(int argc,char** argv){
    /*
    Matrix<int> m(6,6,-1);
    
    m.setValue(0,0,-1);
    m.setValue(1,1,-1);
    m.setValue(2,2,-1);
    m.setValue(3,3,-1);
    m.setValue(4,4,-1);
    m.setValue(5,5,-1);
    
    m.setValue(0,1,780);
    m.setValue(0,2,320);
    m.setValue(0,3,580);
    m.setValue(0,4,480);
    m.setValue(0,5,660);
    
    m.setValue(1,0,780);
    m.setValue(1,2,700);
    m.setValue(1,3,460);
    m.setValue(1,4,300);
    m.setValue(1,5,200);
    
    m.setValue(2,0,320);
    m.setValue(2,1,700);
    m.setValue(2,3,380);
    m.setValue(2,4,820);
    m.setValue(2,5,630);
    
    m.setValue(3,0,580);
    m.setValue(3,1,460);
    m.setValue(3,2,380);
    m.setValue(3,4,750);
    m.setValue(3,5,310);
    
    m.setValue(4,0,480);
    m.setValue(4,1,300);
    m.setValue(4,2,820);
    m.setValue(4,3,750);
    m.setValue(4,5,500);
    
    m.setValue(5,0,660);
    m.setValue(5,1,200);
    m.setValue(5,2,630);
    m.setValue(5,3,310);
    m.setValue(5,4,500);
    */
    
    
    TsplibFile fileInput;
    char fileMode[] = "-o";
    char inputFile[] = "-i";
    Matrix<int> distMatrix(0,0,-1);
    string name;
    stringstream outPut;
            
    
    //flux = std::cout
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],inputFile) == 0){
            TsplibFile fileInput = LoaderFile::load(argv[i+1]);
            distMatrix = fileInput.getMatrix();
            name = fileInput.GetName();
            outPut << "COMMENT : Optimal solution for " 
            << fileInput.GetName() 
            << endl
            << "TYPE : TOUR"
            << endl
            << "DIMENSION : "
            << fileInput.GetDimension()
            << endl
            << "TOUR_SECTION"
            << endl;
        }
    }
    string Ostring = outPut.str();
    bool mode = false;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],fileMode) == 0){
                ofstream fichier(name, ios::out | ios::app);
                int size = distMatrix.getNbRows();
                Way bestWay(size),currentWay(size);
                little(distMatrix,bestWay,currentWay,0,Ostring);
                mode = true;
                fichier << Ostring;
        }
    }
    if(!mode){
        int size = distMatrix.getNbRows();
        Way bestWay(size),currentWay(size);
        little(distMatrix,bestWay,currentWay,0,Ostring);
        cout << Ostring;
    }
}