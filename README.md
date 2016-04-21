# TSP-solver
This is Traveling salesman problem solver, implementing Little's algorithm in C++, it is based on a client-server architecture.
The server is written in C++ and computes the best path to go to every node only once.
The client is a Web GUI which will display the map and will request the server.
The communication between the two is made with Web sockets
