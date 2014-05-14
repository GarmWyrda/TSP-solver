/* 
 * File:   Little.cpp
 * Author: louis
 *
 * Created on April 14, 2014, 3:52 PM
 */

#include <cstdlib>
#include "Little/Little.h"
#include <iostream>
using std::cout;
/*
 * 
 */
void Way::addPoints(int a, int b,int index){
    /*
    int sortedCursor,j;
    this->points[index].setI(a);
    this->points[index].setJ(b);
    Pair currentPair,lastSortedPair; 
    this->lastAdded.setI(a);
    this->lastAdded.setJ(b); 
    cout << a << " " << b;
    for(sortedCursor = 1;sortedCursor < index;sortedCursor++){
        lastSortedPair = this->points[sortedCursor];
        for(j = sortedCursor;j <= index;j++){
            currentPair = this->points[j];
            if(lastSortedPair.getJ() == currentPair.getI()){
                Pair tmp;
                tmp = this->points[sortedCursor+1];
                this->points[sortedCursor+1] = currentPair;
                this->points[j] = tmp;
            }
        }
    }
    for(sortedCursor = 1;sortedCursor < index;sortedCursor++){
        lastSortedPair = this->points[sortedCursor];
        for(j = sortedCursor;j <= index;j++){
            currentPair = this->points[j];
            if(lastSortedPair.getI() == currentPair.getJ()){
                Pair tmp;
                tmp = this->points[sortedCursor-1];
                this->points[sortedCursor-1] = currentPair;
                this->points[j] = tmp;
            }
        }
    }
}*/
    int i = 0;
    bool found = false;
    
    while(!found && i < index){
        if(this->points[i].getJ() == a ){
            found = true;
        }
        else if(this->points[i].getI() == b){
            found = true;
            i--;
        }
        i++;
    }
    Pair tmp1;
    Pair tmp2;
    tmp1 = this->points[i];
    int j;
    for(j=i+1;j<this->points.size();j++){
        tmp2 = this->points[j];
        this->points[j] = tmp1;
        tmp1 = tmp2;
    }
    this->points[i].setI(a);
    this->points[i].setJ(b);
}

/************UTILITY FUNCTIONS******************/
//Returns the minimum of a row in the matrix given
float getMinOnRow(Matrix<int> &matrix, int row){
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
void clearRow(Matrix<int> &matrix, int row, float value){
    for(int i=0;i<matrix.getNbColumns();i++){
        if(matrix.getValue(row,i) != matrix.getEmptyValue()){
                matrix.setValue(row,i,matrix.getValue(row,i)-value);
        }
    }
}

//Get the minimum value in the column at index i in matrix
float getMinOnColumn(Matrix<int> &matrix, int column){   
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
void clearColumn(Matrix<int> &matrix, int column, float value){
    for(int i=0;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue()){
                matrix.setValue(i,column,matrix.getValue(i,column)-value);
        }
    }
}

//This function reduces the matrix, and returns the value of node weight
int reduceMatrix(Matrix<int> &matrix){
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
int getRegret(Matrix<int> &matrix, int row,int col){
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

Regret getMaxRegret(Matrix<int> &matrix){
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
void removeRowAndCol(Matrix<int> &matrix,int row,int col){
    for(int i = 0;i<matrix.getNbColumns();i++){
        matrix.setValue(row,i,matrix.getEmptyValue());
    }
    for(int i = 0;i<matrix.getNbRows();i++){
        matrix.setValue(i,col,matrix.getEmptyValue());
    }
}

void deleteInvalidWays(Matrix<int> &matrix, Way &currentWay, int index){
    if(index != 0){
        Pair addedPair;
        addedPair = currentWay.getPoints()[index-1];
        matrix.setValue(addedPair.getJ(),addedPair.getI(),matrix.getEmptyValue());
        bool headFound = false;
        int headFoundIndex;
        bool tailFound = false;
        int tailFoundIndex;
        Pair currentPair;
        
        for(int i = 0;i < index-1;i++){
            currentPair = currentWay.getPoints()[i];
            if(currentPair.getI() == addedPair.getJ()){
                tailFound = true;
                tailFoundIndex = i;
            }
            if(currentPair.getJ() == addedPair.getI()){
                headFound = true;
                headFoundIndex = i;
            }
        }
        int i;
        if(headFound && !tailFound){
            i = index;
            while(currentWay.getPoints()[i].getJ() != addedPair.getI()){
                i++;
            }
            i--;
            matrix.setValue(i,addedPair.getI(),matrix.getEmptyValue());
        }
        if(!headFound && tailFound){
            i = index-2;
            while(currentWay.getPoints()[i].getI() != addedPair.getJ()){
                i--;
            }
            i++;
            matrix.setValue(addedPair.getJ(),i,matrix.getEmptyValue());
        }
        if(headFound && tailFound){
            
        }
    }
}
/***********************************************/

/*Takes a DistanceMatrix as argument and returns the shortest hamiltonian cycle*/
Way little(Matrix<int> matrix,Way &bestWay,Way &currentWay, int count){
    deleteInvalidWays(matrix,currentWay,count);
    int weight = reduceMatrix(matrix);
    currentWay.setLength(currentWay.getLength() + weight);
    cout << matrix;
    if(currentWay.getLength() >= bestWay.getLength() && bestWay.getLength() != 0){
        return bestWay;
    }
    else{
        if(count == matrix.getNbRows()-2){
            if(currentWay.getLength() < bestWay.getLength() || bestWay.getLength() == 0){
                for(int i = 0; i < matrix.getNbRows();i++){
                    for(int j = 0; j < matrix.getNbColumns();j++){
                        if(matrix.getValue(i,j) != matrix.getEmptyValue()){
                            currentWay.addPoints(i,j,count+1);
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
           Matrix<int> matrix1 = matrix;
           removeRowAndCol(matrix,regret.getI(),regret.getJ());
           Way currentWay2 = currentWay;
           currentWay.addPoints(regret.getI(),regret.getJ(),count);
           cout << currentWay << endl;
           cout << matrix;
           little(matrix,bestWay,currentWay,count + 1);
           if(currentWay.getLength() + regret.getValue() >= bestWay.getLength()){
               return bestWay;
           }
           else{
               matrix1.setValue(regret.getI(),regret.getJ(),matrix1.getEmptyValue());
               little(matrix1,bestWay,currentWay2,count);
           }
        }
    }
   
    return bestWay;
}

Way little(Matrix<int> matrix,Way &bestWay,Way &currentWay,int count, string &flux){
    cout << currentWay << endl;
    deleteInvalidWays(matrix,currentWay,count);
    int weight = reduceMatrix(matrix);
    currentWay.setLength(currentWay.getLength() + weight);
    cout << matrix;
    if(currentWay.getLength() >= bestWay.getLength() && bestWay.getLength() != 0){
        return bestWay;
    }
    else{
        if(count == matrix.getNbRows()-2){
            if(currentWay.getLength() < bestWay.getLength() || bestWay.getLength() == 0){
                for(int i = 0; i < matrix.getNbRows();i++){
                    for(int j = 0; j < matrix.getNbColumns();j++){
                        if(matrix.getValue(i,j) != matrix.getEmptyValue()){
                            currentWay.addPoints(i,j,count+1);
                            currentWay.setLength(matrix.getValue(i,j) + currentWay.getLength());
                            cout << currentWay << endl;
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
           Matrix<int> matrix1 = matrix;
           removeRowAndCol(matrix,regret.getI(),regret.getJ());
           cout << matrix;
           Way currentWay2 = currentWay;
           currentWay.addPoints(regret.getI(),regret.getJ(),count);
           cout << currentWay << endl;
           little(matrix,bestWay,currentWay,count + 1,flux);
           if(currentWay.getLength() + regret.getValue() >= bestWay.getLength()){
               return bestWay;
           }
           else{
               matrix1.setValue(regret.getI(),regret.getJ(),matrix1.getEmptyValue());
               little(matrix1,bestWay,currentWay2,count,flux);
           }
        }
    }
    for(int i = 0;i<bestWay.getLength();i++){
        flux += bestWay.getPoints()[i].getI();
        flux += " ";
    }
    flux += "\n-1\nEOF";
    return bestWay;
}
