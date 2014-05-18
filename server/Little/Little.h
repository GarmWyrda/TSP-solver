/* 
 * File:   Little.h
 * Author: Louis
 *
 * Created on March 24, 2014, 2:06 PM
 */

#ifndef LITTLE_H
#define	LITTLE_H
#include "../Matrix/matrix.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../Obspattern.h"
// boost threads
#include <boost/thread.hpp>
#include "../Way.h"
#define _WEBSOCKETPP_CPP11_STL_
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;
using std::stringstream;
using std::string;

class LittleObs : public Observateur{
private:
    server::connection_ptr conn;
public:
    LittleObs(server::connection_ptr conn){this->conn = conn;};
    ~LittleObs(){};
    void Update(Observable* observable);
};

class Regret{
private:
    int i,j;
    float value;
public:
    Regret(int i = 0,int j = 0,float value = 0){this->i = i;this->j = j;this->value = value;};
    ~Regret(){};
    
    float getValue(){return this->value;};
    float getI(){return this->i;};
    float getJ(){return this->j;};
};


class Little : public Observable{
private:
    Matrix<int> distMatrix;
    Way bestWay;
    boost::thread* pThread; // The thread runs this object
    static bool isRunning;
    
    Little(Matrix<int> distMatrix, Way bestWay);
    ~Little(){Little::isRunning = false;};
    Way solve(Matrix<int> matrix,Way &bestWay,Way &currentWay, int count);
    void deleteInvalidWays(Matrix<int> &matrix, Way &currentWay, int index);
    void removeRowAndCol(Matrix<int> &matrix,int row,int col);
    Regret getMaxRegret(Matrix<int> &matrix);
    int getRegret(Matrix<int> &matrix, int row,int col);
    int reduceMatrix(Matrix<int> &matrix);
    void clearColumn(Matrix<int> &matrix, int column, float value);
    float getMinOnColumn(Matrix<int> &matrix, int column);
    void clearRow(Matrix<int> &matrix, int row, float value);
    float getMinOnRow(Matrix<int> &matrix, int row);
    void setBestWay(Way &way);
    
public:
    Way Statut(void);
    static Way call(Matrix<int>& distMatrix, LittleObs* obs=NULL);
};

class AlreadyRunningEx{
};


#endif

