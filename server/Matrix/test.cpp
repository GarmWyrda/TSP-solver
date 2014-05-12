#include "matrix.h"
#include "TestStats.h"
#include "../Little/Little.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include "../tspParse.h"
#include <sstream>
#include <string>
using namespace std;

int main(int argc,char** argv){
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