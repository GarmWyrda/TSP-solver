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

/************UTILITY FUNCTIONS******************/
//Returns the minimum of a row in the matrix given
template<class T> T getMinOnRow(Matrix<T> &matrix, int row){
    int index = 0;
    while(matrix.getValue(row,index) == matrix.getEmptyValue()){
        index++;
    }
    T min = matrix.getValue(row,index);
    for(int i=index+1;i<matrix.getNbColumns();i++){
            if(matrix.getValue(row,i)!=matrix.getEmptyValue() && matrix.getValue(row,i)<min){
                min = matrix.getValue(row,i);
            }
    }
    return min;
}
//Substract value into each cell of the row in matrix
template<class T> void clearRow(Matrix<T> &matrix, int row, T value){
    for(int i=0;i<matrix.getNbColumns();i++){
        if(matrix.getValue(row,i) != matrix.getEmptyValue()){
                matrix.setValue(row,i,matrix.getValue(row,i)-value);
        }
    }
}

//Get the minimum value in the column at index i in matrix
template<class T> T getMinOnColumn(Matrix<T> &matrix, int column){   
    int index = 0;
    while(matrix.getValue(index,column) == matrix.getEmptyValue()){
        index++;
    }
    T min = matrix.getValue(index,column);
    for(int i=index+1;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue() && matrix.getValue(i,column)<min){
            min = matrix.getValue(i,column);
        }
    }
    return min;
}

//Substract the value in each cell of the column in the matrix
template<class T> void clearColumn(Matrix<T> &matrix, int column, T value){
    for(int i=0;i<matrix.getNbRows();i++){
        if(matrix.getValue(i,column)!= matrix.getEmptyValue()){
                matrix.setValue(i,column,matrix.getValue(i,column)-value);
        }
    }
}

//This function reduces the matrix, and returns the value of node weight
template<class T> T reduceMatrix(Matrix<T> &matrix){
    T min;
    T sum=0;
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
template<class T> T getRegret(Matrix<T> &matrix, int row,int col){
    T sum = 0;
    int index1 = 0;
    while(matrix.getValue(row,index1) == matrix.getEmptyValue() || index1 == col){
        index1++;
    }
    T minRow = matrix.getValue(row,index1);
    int index2 = 0;
    while(matrix.getValue(index2,col) == matrix.getEmptyValue() || index2 == row){
        index2++;
    }
    T minCol = matrix.getValue(index2,col);
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

template<class T> T getMaxRegret(Matrix<T> &matrix){
    T maxRegret = -1;
    T currentRegret;
    for(int i = 0;i<matrix.getNbRows();i++){
        for(int j = 0;j<matrix.getNbColumns();j++){
            if(matrix.getValue(i,j) == 0){
                currentRegret = getRegret(matrix,i,j);
                if(currentRegret > maxRegret){
                    maxRegret = currentRegret;
                }
            }
        }
    }
    
}

/***********************************************/
/*Takes a DistanceMatrix as argument and returns the shortest hamiltonian cycle*/
template<class T> void little(Matrix<T> matrix,ostream &flux){
    T weight = reduceMatrix(matrix);
}


#endif	/* LITTLE_H */
