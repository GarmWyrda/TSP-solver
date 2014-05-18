/* 
 * File:   Little.cpp
 * Author: louis
 *
 * Created on April 14, 2014, 3:52 PM
 */

#include <cstdlib>
#include "Little/Little.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
/*
 * 
 */
void Way::addPoints(int a, int b,int index){
    this->points[index].setI(a);
    this->points[index].setJ(b);
}

/************UTILITY FUNCTIONS******************/
//Returns the minimum of a row in the matrix given
float Little::getMinOnRow(Matrix<int> &matrix, int row){
    int index = 0;
    while(index < matrix.getNbRows() && matrix.getValue(row,index) == matrix.getEmptyValue()){
        index++;
    }
    if(index >= matrix.getNbRows()){
        return 0;
    }
    int min = matrix.getValue(row,index);
    for(int i=index+1;i<matrix.getNbColumns();i++){
            if(matrix.getValue(row,i)!=matrix.getEmptyValue() && matrix.getValue(row,i)<min){
                min = matrix.getValue(row,i);
            }
    }
    return min;
}
//Substract value into each cell of the row in matrix
void Little::clearRow(Matrix<int> &matrix, int row, float value){
    for(int i=0;i<matrix.getNbColumns();i++){
        if(matrix.getValue(row,i) != matrix.getEmptyValue()){
                matrix.setValue(row,i,matrix.getValue(row,i)-value);
        }
    }
}

//Get the minimum value in the column at index i in matrix
float Little::getMinOnColumn(Matrix<int> &matrix, int column){   
    int index = 0;
    while(index < matrix.getNbColumns() && matrix.getValue(index,column) == matrix.getEmptyValue()){
        index++;
    }
    if(index >= matrix.getNbColumns()){
        return 0;
    }
    int min = matrix.getValue(index,column);
    for(int i=index+1;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue() && matrix.getValue(i,column)<min){
            min = matrix.getValue(i,column);
        }
    }
    return min;
}

//Substract the value in each cell of the column in the matrix
void Little::clearColumn(Matrix<int> &matrix, int column, float value){
    for(int i=0;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue()){
                matrix.setValue(i,column,matrix.getValue(i,column)-value);
        }
    }
}

//This function reduces the matrix, and returns the value of node weight
int Little::reduceMatrix(Matrix<int> &matrix){
    int min;
    int sum=0;
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
int Little::getRegret(Matrix<int> &matrix, int row,int col){
    int sum = 0;
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
            if(matrix.getValue(row,i) < minRow && matrix.getValue(row,i) != matrix.getEmptyValue()){
                minRow = matrix.getValue(row,i);
            }
        }
    }
    for(int i=index2+1;i<matrix.getNbRows();i++){
        if(i!=row){
            if(matrix.getValue(i,col) < minCol && matrix.getValue(i,col) != matrix.getEmptyValue()){
                minCol = matrix.getValue(i,col);
            }
        }
    }
    sum = minCol + minRow;
    return sum;
}

Regret Little::getMaxRegret(Matrix<int> &matrix){
    int maxRegret = -1;
    int currentRegret;
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
void Little::removeRowAndCol(Matrix<int> &matrix,int row,int col){
    for(int i = 0;i<matrix.getNbColumns();i++){
        matrix.setValue(row,i,matrix.getEmptyValue());
    }
    for(int i = 0;i<matrix.getNbRows();i++){
        matrix.setValue(i,col,matrix.getEmptyValue());
    }
}     //penser à Chasles? penser permutation, cycle, "borne" des cycles = ce qu'il faut supprimer...    

void Little::deleteInvalidWays(Matrix<int> &matrix, Way &currentWay, int index){
    int i, val; 
    if(index == 0){ return; }
    int tmpDepart, tmpArrival; 
    tmpDepart = currentWay.getPoints()[index-1].getI(); 
    tmpArrival = currentWay.getPoints()[index-1].getJ();
    vector<int> list; 
    list = vector<int> (0, 0); 
    list.insert(list.begin(), tmpDepart); 
    list.push_back(tmpArrival);
    for(i=0; i<index; i++){ 
        val = currentWay.getPoints()[i].getJ(); 
        if(val == tmpDepart){
            tmpDepart = currentWay.getPoints()[i].getI(); 
            list.insert(list.begin(), tmpDepart);
            i = -1; 
        } 
        if(list.size() > matrix.getNbColumns())
        {
            return; 
        } 
    } 
    for(i=0; i<index; i++){
        val = currentWay.getPoints()[i].getI(); 
        if(val == tmpArrival){
            tmpArrival = currentWay.getPoints()[i].getJ(); 
            list.push_back(tmpArrival);
            i = -1;
        }
        if(list.size() > matrix.getNbColumns()){ return; } 
    } 
    tmpDepart = list[list.size() - 1]; 
    tmpArrival = list[0];
    matrix.setValue(tmpDepart, tmpArrival, -1);
}


Way Little::solve(Matrix<int> matrix,Way &bestWay,Way &currentWay,int count){
    deleteInvalidWays(matrix,currentWay,count);
    cout << currentWay << endl;
    cout << matrix<< endl;
    int weight = reduceMatrix(matrix);
    cout << matrix<< endl;
    currentWay.setLength(currentWay.getLength() + weight);
    if(currentWay.getLength() >= bestWay.getLength() && bestWay.getLength() != 0){
        cout << bestWay <<endl;
        return bestWay;
    }
    else{
        if(count == matrix.getNbRows()-2){
            if(currentWay.getLength() < bestWay.getLength() || bestWay.getLength() == 0){
                for(int i = 0; i < matrix.getNbRows();i++){
                    for(int j = 0; j < matrix.getNbColumns();j++){
                        if(matrix.getValue(i,j) != matrix.getEmptyValue()){
                            currentWay.addPoints(i,j,count);
                            currentWay.setLength(matrix.getValue(i,j) + currentWay.getLength());
                            count++;
                        }
                    }
                }
                setBestWay(currentWay);
                cout << bestWay <<endl;
                return bestWay;
            }
            else{
                cout << bestWay <<endl;
                return bestWay;
            }
        }
        else{
           Regret regret = getMaxRegret(matrix);
           Matrix<int> matrix1 = matrix;
           removeRowAndCol(matrix,regret.getI(),regret.getJ());
           cout << matrix<< endl;
           Way currentWay2 = currentWay;
           currentWay.addPoints(regret.getI(),regret.getJ(),count);
           solve(matrix,bestWay,currentWay,count + 1);
           if(currentWay.getLength() + regret.getValue() >= bestWay.getLength()){
               cout << bestWay <<endl;
               return bestWay;
           }
           else{
               matrix1.setValue(regret.getI(),regret.getJ(),matrix1.getEmptyValue());
               solve(matrix1,bestWay,currentWay2,count);
           }
        }
    }
    cout << bestWay <<endl;
    return bestWay;
}

Way Little::call(Matrix<int> &matrix){
    if(Little::isRunning){
        throw AlreadyRunningEx();
    }
    Way bestWay(matrix.getNbRows());
    Little newLittle(matrix,bestWay);
    Way currentWay(matrix.getNbRows());
    return newLittle.solve(newLittle.distMatrix,bestWay,currentWay,0);
}

Little::Little(Matrix<int> distMatrix, Way bestWay): distMatrix(distMatrix){
    this->bestWay = bestWay;
    this->pThread = NULL;
    Little::isRunning = true;
}

bool Little::isRunning = false;

void Little::setBestWay(Way &way){
    this->bestWay = way;
    Notify();
}

Way Little::Statut(){
    return this->bestWay;
}

void LittleObs::Update(Observable* observable){
    string output;
    output += observable->Statut().toString();
    output += ", \"state\" : \"ongoing\" ";
    
}