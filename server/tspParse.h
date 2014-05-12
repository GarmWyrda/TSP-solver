/* 
 * File:   tspParse.h
 * Author: louis
 *
 * Created on May 4, 2014, 3:42 PM
 */

#ifndef TSPPARSE_H
#define	TSPPARSE_H
#include <fstream>
#include <cstring>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <stdlib.h>
#include <map>
#include "Matrix/matrix.h"
using std::cout;
using std::string;
using std::endl;
using std::ifstream;
using std::vector;
using std::map;


class TsplibFile{
public:
    TsplibFile(): EdgeWeghtMatrix(Matrix<int>(0,0,-1)){
        this->info = map<string, string>();
        //this->EdgeWeghtMatrix = Matrix<int>(0,0,-1);
    };
    
    void createSquareMatrix(const int size);
    void printMatrix(){
        cout << this->EdgeWeghtMatrix;
    }
    Matrix<int>& getMatrix(){
        return this->EdgeWeghtMatrix;
    }
    
    void setEdgeValue(int i, int j, int value){
        this->EdgeWeghtMatrix.setValue(i, j, value);
    }
    //TsplibFile(const TsplibFile& orig);
    virtual ~TsplibFile(){};

    const string& GetDimension() const {
        return this->Get("DIMENSION");
    }

    void SetDimmension(string dimension) {
        this->Set("DIMENSION", dimension);
    }

    const string& GetDisplay_data_type() const {
        return this->Get("DISPLAY_DATA_TYPE");
    }

    void SetDisplay_data_type(string display_data_type) {
        this->Set("DISPLAY_DATA_TYPA", display_data_type);
    }

    const string& GetEdge_data_format() const {
        return this->Get("EDGE_DATA_FORMAT");
    }

    void SetEdge_data_format(string edge_data_format) {
        this->Set("EDGE_DATA_FORMAT", edge_data_format);
    }

    const string& GetEdge_weight_format() const {
        return this->Get("EDGE_WEGHT_FORMAT");
    }

    void SetEdge_weight_format(string edge_weight_format) {
        this->Set("EDGE_WEIGHT_FORMAT",edge_weight_format);
    }

    const string& GetEdge_weight_type() const {
        return this->Get("EDGE_WEIGHT_TYPE");
    }

    void SetEdge_weight_type(string edge_weight_type) {
        this->Set("EDGE_WEIGHT_TYPE", edge_weight_type);
    }

    const string& GetName() const {
        return this->Get("NAME");
    }

    void SetName(string name) {
        this->Set("NAME",name);
    }

    const string& GetNode_coord_type() const {
        return this->Get("NODE_COORD_TYPE");
    }

    void SetNode_coord_type(string node_coord_type) {
        this->Set("NODE_COORD_TYPE",node_coord_type);
    }

    const string& GetType() const {
        return this->Get("TYPE");
    }

    void SetType(string type) {
        this->Set("TYPE",type);
    }
    
    friend std::ostream& operator<<(std::ostream& stream, TsplibFile& orig){
        stream << "TSPLIB file : " << orig.GetName() << std::endl;
        auto ite = orig.info.begin();
        for(auto ite = orig.info.begin(); ite != orig.info.end(); ite++){
            stream << ite->first << " : " << ite->second << std::endl;
        }
        return stream << orig.EdgeWeghtMatrix;
    }

private:
    map<string, string> info;
    Matrix<int> EdgeWeghtMatrix;
    const string& Get(string key) const {
        return this->info.find(key)->second;
    }

    void Set(string key, string val) {
        this->info.insert(std::pair<string,string>(key, val));
    }

};



class LoaderFile {
public:
    static TsplibFile load(const string& path);
private:
    LoaderFile();
    bool readEdgeSection(ifstream& file, const string& format, const string& dim, TsplibFile& tslibfile);
    void setFulllMatrix(ifstream& file, const int& dim, TsplibFile& tsplibfile);
    void set(ifstream& file, const int& dim, TsplibFile& tsplibfile);
    void setDiag(ifstream& file, const int& dim, TsplibFile& tsplibfile);

    bool is_number(const std::string& s) {
        return !s.empty() && std::isdigit(s[0]);
    }
    //    LoaderFile(const LoaderFile& orig);
    //    virtual ~LoaderFile();
};

class FileException{
private:
    string error;
public:
    FileException(){};
    FileException(string stringErr = " "){this->error = stringErr;};
    
};

#endif	/* TSPPARSE_H */

