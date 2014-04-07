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
    void addPoints(int a, int b,int index){this->points[index].setI(a);this->points[index].setJ(b);}
    vector<Pair>& getPoints(){return this->points;};
    Pair operator[](int index){return this->points[index];};
    
};

/************UTILITY FUNCTIONS******************/
//Returns the minimum of a row in the matrix given
float getMinOnRow(Matrix<float> &matrix, int row){
    int index = 0;
    while(matrix.getValue(row,index) == matrix.getEmptyValue()){
        index++;
    }
    float min = matrix.getValue(row,index);
    for(int i=index+1;i<matrix.getNbColumns();i++){
            if(matrix.getValue(row,i)!=matrix.getEmptyValue() && matrix.getValue(row,i)<min){
                min = matrix.getValue(row,i);
            }
    }
    return min;
}
//Substract value into each cell of the row in matrix
void clearRow(Matrix<float> &matrix, int row, float value){
    for(int i=0;i<matrix.getNbColumns();i++){
        if(matrix.getValue(row,i) != matrix.getEmptyValue()){
                matrix.setValue(row,i,matrix.getValue(row,i)-value);
        }
    }
}

//Get the minimum value in the column at index i in matrix
float getMinOnColumn(Matrix<float> &matrix, int column){   
    int index = 0;
    while(matrix.getValue(index,column) == matrix.getEmptyValue()){
        index++;
    }
    float min = matrix.getValue(index,column);
    for(int i=index+1;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue() && matrix.getValue(i,column)<min){
            min = matrix.getValue(i,column);
        }
    }
    return min;
}

//Substract the value in each cell of the column in the matrix
void clearColumn(Matrix<float> &matrix, int column, float value){
    for(int i=0;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue()){
                matrix.setValue(i,column,matrix.getValue(i,column)-value);
        }
    }
}

//This function reduces the matrix, and returns the value of node weight
float reduceMatrix(Matrix<float> &matrix){
    float min;
    float sum=0;
    for(int i = 0;i<matrix.getNbRows();i++){
        min = getMinOnRow(matrix,i);
        sum += min;
        clearRow(matrix,i,min);
    }
    for(int i = 0;i<matrix.getNbColumns();i++){
        min = getMinOnColumn(matrix,i);
        sum += min;
        clearColumn(matrix,i,min);
    }
    return sum;
}

//Retourne le regret dans la case (i,j) de matrix
float getRegret(Matrix<float> &matrix, int row,int col){
    float sum = 0;
    int index1 = 0;
    while(matrix.getValue(row,index1) == matrix.getEmptyValue() || index1 == col){
        index1++;
    }
    float minRow = matrix.getValue(row,index1);
    int index2 = 0;
    while(matrix.getValue(index2,col) == matrix.getEmptyValue() || index2 == row){
        index2++;
    }
    float minCol = matrix.getValue(index2,col);
    for(int i=index1+1;i<matrix.getNbColumns();i++){
        if(i!=col){
            if(matrix.getValue(row,i) < minRow){
                minRow = matrix.getValue(row,i);
            }
        }
    }
    for(int i=index2+1;i<matrix.getNbRows();i++){
        if(i!=row){
            if(matrix.getValue(i,col) < minCol){
                minRow = matrix.getValue(i,col);
            }
        }
    }
    sum = minCol + minRow;
    return sum;
}

Regret getMaxRegret(Matrix<float> &matrix){
    float maxRegret = -1;
    float currentRegret;
    int row;
    int col;
    for(int i = 0;i<matrix.getNbRows();i++){
        for(int j = 0;j<matrix.getNbColumns();j++){
            if(matrix.getValue(i,j) == 0){
                currentRegret = getRegret(matrix,i,j);
                if(currentRegret > maxRegret){
                    maxRegret = currentRegret;
                    row = i;
                    col = j;
                }
            }
        }
    }
    Regret returnValue(row,col,maxRegret);
    return returnValue;
}

/*Instead of removing a row and a column with matrix type which is costly we set all the values in the row and 
 the column to an invalid one, -1 for instance*/
void removeRowAndCol(Matrix<float> &matrix,int row,int col){
    for(int i = 0;i<matrix.getNbColumns();i++){
        matrix.setValue(row,i,matrix.getEmptyValue());
    }
    for(int i = 0;i<matrix.getNbRows();i++){
        matrix.setValue(i,col,matrix.getEmptyValue());
    }
}
void deleteInvalidWays(Matrix<float> &matrix, Way &currentWay, int index){
    if(index != 0){
        Pair pair = currentWay[index-1];
        matrix.setValue(pair.getJ(),pair.getI(),matrix.getEmptyValue()); 
        for(int i = 0;i < index-1;i++){
        }
    }
}
/***********************************************/

/*Takes a DistanceMatrix as argument and returns the shortest hamiltonian cycle*/
Way little(Matrix<float> matrix,ostream &flux,Way &bestWay,Way currentWay, int count=0){
    deleteInvalidWays(matrix,currentWay,count);
    float weight = reduceMatrix(matrix);
    currentWay.setLength(currentWay.getLength() + weight);
    if(currentWay.getLength() >= bestWay.getLength() && bestWay.getLength() != -1){
        return bestWay;
    }
    else{
        if(count = matrix.getNbRows()-2){
            if(currentWay.getLength() < bestWay.getLength() || bestWay.getLength() == -1){
                for(int i = 0; i < matrix.getNbRows();i++){
                    for(int j = 0; j < matrix.getNbColumns();j++){
                        if(matrix.getValue(i,j) != matrix.getEmptyValue()){
                            currentWay.setLength(matrix.getValue(i,j) + currentWay.getLength());
                            count++;
                        }
                    }
                }
                bestWay = currentWay;
                return bestWay;
            }
            else{
                return bestWay;
            }
        }
        else{
           Regret regret = getMaxRegret(matrix);
           Matrix<float> matrix1 = matrix;
           removeRowAndCol(matrix,regret.getI(),regret.getJ());
           currentWay.addPoints(regret.getI(),regret.getJ(),count);
           little(matrix,flux,bestWay,currentWay,count + 1);
           if(currentWay.getLength() + regret.getValue() >= bestWay.getLength()){
               return bestWay;
           }
           else{
               matrix1.setValue(regret.getI(),regret.getJ(),matrix1.getEmptyValue());
               little(matrix1,flux,bestWay,currentWay,count);
           }
        }
    }
    return bestWay;
}

#endif	/* LITTLE_H */

