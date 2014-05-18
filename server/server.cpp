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


#define _WEBSOCKETPP_CPP11_STL_
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <sstream>
#include <functional>
#include <string>
#include <stdlib.h>

using namespace boost::property_tree;
using std::bind;
using std::string;
using std::stringstream;

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;

class Logger {
public:

    static ostream& log(ostream& os, string message) {
        time_t t = time(NULL);
        tm* lt = localtime(&t);
        char buffer[20];

        strftime(buffer, sizeof (buffer), "%Y-%m-%d %H:%M:%S", lt);
        return os << "[" << buffer << "] " << message << endl;
    }
};

class Request{
private:
    string type;
    Matrix<int>* matrix;
    server::connection_ptr conn;
public:
    Request(string type,server::connection_ptr conn, Matrix<int>* matrix=NULL );
    ~Request();
    string getType(){return this->type;};
    Matrix<int> getMatrix(){if(matrix!=NULL){return *this->matrix;}};
    void handle();
    
};

Request::Request(string type,server::connection_ptr conn, Matrix<int>* matrix ){
    this->type=type;
    this->matrix=matrix;
    this->conn=conn;
    if(matrix!=NULL){
        this->matrix = new Matrix<int>(matrix->getNbRows(),matrix->getNbColumns(),matrix->getEmptyValue());
        for(int i = 0;i<matrix->getNbRows();i++){
            for(int j = 0;j<matrix->getNbColumns();j++){
                this->matrix->setValue(i,j,matrix->getValue(i,j));
            }
        }
    }
}
void Request::handle(){
    stringstream msg;
    Way result;
    if(type == "play"){
        if(matrix != NULL && matrix->getNbRows() >= 0){
                std::cout << "Calling Little algorithm for client : " << conn->get_remote_endpoint() << std::endl;
                std::cout << *matrix << std::endl;
                LittleObs* obs;
                obs = new LittleObs(this->conn);
                result = Little::call(*matrix,obs);
                msg << result;
                msg << ", \"state\" : \"finished\" , \"type\" : \"little\"}";
                cout << msg.str() << endl;
                this->conn->send(msg.str());
        }
        else{
            msg << "{\"type\":\"error\" , \"msg\":\"invalidMatrix\"}";
            this->conn->send(msg.str());
        }
    }
    else if(type == "pause"){
        stringstream msg;
        msg << "{\"type\":\"success\" , \"msg\":\"Pausing calculation\"}";
        this->conn->send(msg.str());
    }
    else if(type == "stop"){
        stringstream msg;
        msg << "{\"type\":\"success\" , \"msg\":\"Stopping calculation\"}";
        this->conn->send(msg.str());
    }
}

class Server {
private:
    server ws_server;

public:

    Server() {
        ws_server.init_asio();

        // disable default loggers
        ws_server.clear_access_channels(websocketpp::log::alevel::all);
        ws_server.clear_error_channels(websocketpp::log::alevel::all);


        ws_server.set_open_handler(bind(&Server::onOpen, this, ::_1));
        ws_server.set_close_handler(bind(&Server::onClose, this, ::_1));
        ws_server.set_message_handler(bind(&Server::onMessage, this, ::_1, ::_2));
    }

    void onOpen(connection_hdl hdl) {
        server::connection_ptr conn = this->ws_server.get_con_from_hdl(hdl);
        cout << "Client connected from : " << conn->get_remote_endpoint() << endl;
    }
    void onClose(connection_hdl hdl) {
        server::connection_ptr conn = this->ws_server.get_con_from_hdl(hdl);
        cout << "Client disconnected : " << conn->get_remote_endpoint() << endl;
    }

    void onMessage(connection_hdl hdl, server::message_ptr msg) {
        server::connection_ptr conn = this->ws_server.get_con_from_hdl(hdl);
        string message = msg->get_payload();

        std::cout << "Received message, " << message << std::endl;
        Request* req=NULL;
        req = processJSON(message,conn);
        if(req != NULL){
                req->handle();
        }

    }

    Request* processJSON(string json,server::connection_ptr conn) {

        stringstream s;
        s << json;

        ptree pt;
        read_json(s, pt);
        Request* req=NULL;
        
            string type = pt.get_child("type").data();

            if (type == "play") {
                int size = pt.get<int>("size");
                if(size == 0){
                    req = new Request(type,conn);
                    return req;
                }
                Matrix<int> matrix = Matrix<int>(size,size,-1);
                int i = 0;
                for(const ptree::value_type &v : pt.get_child("matrix")) {
                    int j = 0;
                    for(const ptree::value_type &w : v.second) {
                        if(j != i){
                            matrix.setValue(i,j,w.second.get_value<int>());
                        }else{
                            matrix.setValue(i,j,matrix.getEmptyValue());
                        }
                        j++;
                    }
                    i++;                 
                }
                req = new Request(type,conn,&matrix);
            }
            else if(type == "pause"){
                std::cout << "Pausing computation" << std::endl;
                req = new Request(type,conn);
                
            }
            else if(type == "stop"){
                std::cout << "Stoping computation" << std::endl;
                req = new Request(type,conn);
            }
            return req;

        
    }

    void run(int port) {
        std::cout << "Listening on port " << port << std::endl;
        //        this->ws_server.init_asio();
        this->ws_server.listen(port);
        this->ws_server.start_accept();
        this->ws_server.run();
    }
};

int main(int argc, char** argv) {
    Server server;
    int port = atoi(argv[argc - 1]);
    server.run(port);
}

/*
int main1(int argc,char** argv){

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
}*/