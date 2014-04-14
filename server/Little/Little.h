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
using std::vector;

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

class Pair{
private:
    int i,j;
public:
    Pair(int i=0,int j = 0){this->i = i; this->j=j;};
    Pair(const Pair &pair){this->i = pair.i; this->j = pair.i;};
    
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
    Pair operator[](int index){return this->points[index];};
    
};

#endif

