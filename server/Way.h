/* 
 * File:   Way.h
 * Author: louis
 *
 * Created on May 18, 2014, 4:19 PM
 */

#ifndef WAY_H
#define	WAY_H
#include <string>
using std::string;
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
    string toString(){
        string flux;
        flux += "{";
        flux += "\"cost\" : \"";
        flux += this->length;
        flux += "\"";
        flux += " , ";
        flux += "\"way\" : \"[";
        int i;
        for(i = 0;i<this->points.size()-1;i++){
            flux += "[";
            flux += this->points[i].getI();
            flux += ",";
            flux += this->points[i].getJ();
            flux += "],";
        }
        flux += "[";
        flux += this->points[i].getI();
        flux += ",";
        flux += this->points[i].getJ();
        flux +="]]";
        return flux;
    }
    friend ostream& operator<<( ostream &flux, Way &way ){
        flux << "{";
        flux << "\"cost\" : \""<< way.length << "\"";
        flux << " , ";
        flux << "\"way\" : \"[";
        int i;
        for(i = 0;i<way.points.size()-1;i++){
            flux << "[" << way.points[i].getI() << "," << way.points[i].getJ() << "],";
        }
        flux << "[" << way.points[i].getI() << "," << way.points[i].getJ() << "]]";
        return flux;
    }
    
};




#endif	/* WAY_H */

