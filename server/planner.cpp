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

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;

string parse_method(string message) {
	ptree tree;
	
	std::stringstream json;
	json << message;

	read_json(json, tree);
	string method = tree.get<string>("method");

	return method;
}

ptree parse_params(string message) {
        ptree tree;

        std::stringstream json;
        json << message;

	read_json(json, tree);

	ptree params = tree.get_child("params");
	return params;
}

class Server {
private:
	server ws_server;

public:
	Server() {
		this->ws_server.set_message_handler(bind(&Server::on_message, this, std::placeholders::_1, std::placeholders::_2));
	}

	void hello(server::connection_ptr conn, ptree params) {
		conn->send("{\"method\" : \"hello\", \"data\" : \"I'm the hello method, HELLO !\"}");
	}

	void on_message(connection_hdl hdl, server::message_ptr msg) {
		server::connection_ptr conn = this->ws_server.get_con_from_hdl(hdl);
		string message = msg->get_payload();

		string method = parse_method(message);
		ptree params = parse_params(message);

		if (method == "hello") {
			this->hello(conn, params);
		}

	}

	void run(int port) {
		    this->ws_server.init_asio();
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
