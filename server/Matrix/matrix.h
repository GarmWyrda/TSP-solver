/* 
 * File:   matrix.h
 * Author: Louis
 *
 * Created on March 10, 2014, 1:57 PM
 */

#ifndef MATRIX_H
#define	MATRIX_H
#include <vector>
#include "IndexOutOfBoundsException.h" // fichier à créer et chemin à changer selon l'organisation de votre projet
using std::vector;

template<class T> class Matrix{
    private:
        int rows;
        int cols;
        int emptyVal;
        vector< vector<T*> > data;

    public :

    // -------------- interdit de modifier cette partie -------------- //
    Matrix(int nbRows, int nbColumns, T emptyValue);

    T getEmptyValue();//done

    int getNbRows();// done
    void addRow(int rowIndex) throw(IndexOutOfBoundsException);
    void removeRow(int rowIndex) throw(IndexOutOfBoundsException);

    int getNbColumns();// done
    void addColumn(int colIndex) throw(IndexOutOfBoundsException);
    void removeColumn(int colIndex) throw(IndexOutOfBoundsException);

    T getValue(int rowIndex, int colIndex) throw(IndexOutOfBoundsException);
    void setValue(int rowIndex, int colIndex, T value) throw(IndexOutOfBoundsException);

    ~Matrix();
    // --------------------------------------------------------------- //

};

template<class T> Matrix<T>::Matrix(int nbRows,int nbColumns,T emptyValue){
    if(nbRows < 0){
        nbRows = 0;
    }
    if(nbColumns){
        nbColumns = 0;
    }
    this->rows = nbRows;
    this->cols = nbColumns;
    this->emptyVal = emptyValue;
    this->data = vector< vector<T*> >(nbRows);
    for(int&i:this->data){
        this->data[i] = vector<T*>(nbColumns,NULL);
    }
};

template<class T> int Matrix<T>::getNbRows(){
    return this->rows;
};
template<class T> int Matrix<T>::getNbColumns(){
    return this->cols;
};
template<class T> T Matrix<T>::getEmptyValue(){
    return this->emptyVal;
};

template<class T> void Matrix<T>::addRow(int rowIndex) throw(IndexOutOfBoundsException){
    if (rowIndex<0 ){
        IndexOutOfBoundsException(rowIndex,0,false);
    }
    if (rowIndex>this->rows) {
        IndexOutOfBoundsException(rowIndex,this->rows,false);
    }
    vector<vector<T*> > row;
    
    this->data.insert(rowIndex,row);
    row.assign(this->cols-1,this->emptyVal);
    this->rows ++ ;

};
#endif	/* MATRIX_H */

