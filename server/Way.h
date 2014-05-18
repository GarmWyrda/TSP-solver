/* 
 * File:   Way.h
 * Author: louis
 *
 * Created on May 18, 2014, 4:19 PM
 */

#ifndef WAY_H
#define	WAY_H
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;
using std::string;
using std::vector;
class Pair{
private:
    int i,j;
public:
    Pair(int i=0,int j = 0){this->i = i; this->j=j;};
    Pair(const Pair &pair){this->i = pair.i; this->j = pair.j;};
    
    int getI(){return this->i;};
    int getJ(){return this->j;};
    void setI(int i){this->i = i;};
    void setJ(int j){this->j = j;};
};

class Way{
private:
    vector<Pair> points;
    float length;
public:
    Way(int n=0){this->points = vector<Pair>(n);this->length = 0;};
    Way(const Way &way){this->points = way.points; this->length = way.length;};
    ~Way(){};
    
    void setLength(float l){this->length = l;};
    float getLength(){return this->length;};
    void addPoints(int a, int b,int index);
    vector<Pair>& getPoints(){return this->points;};

    friend ostream& operator<<( ostream &flux, Way &way ){
        flux << "{\"cost\":\"" << way.length << "\"";
        flux << ",";
        flux << "\"way\":[";
        int i;
        for(i = 0;i<way.points.size()-1;i++){
            flux << "[" << way.points[i].getI()+1 << "," << way.points[i].getJ()+1 << "],";
        }
        flux << "[" << way.points[i].getI()+1 << "," << way.points[i].getJ()+1 << "]]";
        return flux;
    }
    
};




#endif	/* WAY_H */

