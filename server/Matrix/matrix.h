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

template<class T> class Matrix {
private:
    int rows;
    int cols;
    int emptyVal;
    vector< vector<T> > data;

public:

    // -------------- interdit de modifier cette partie -------------- //
    Matrix(int nbRows, int nbColumns, T emptyValue); //done

    T getEmptyValue(); //done

    int getNbRows(); // done
    void addRow(int rowIndex) throw (IndexOutOfBoundsException); //done
    void removeRow(int rowIndex) throw (IndexOutOfBoundsException);

    int getNbColumns(); // done
    void addColumn(int colIndex) throw (IndexOutOfBoundsException);// done
    void removeColumn(int colIndex) throw (IndexOutOfBoundsException);

    T getValue(int rowIndex, int colIndex) throw (IndexOutOfBoundsException);
    void setValue(int rowIndex, int colIndex, T value) throw (IndexOutOfBoundsException);

    ~Matrix(); //done
    // --------------------------------------------------------------- //

};

template<class T> Matrix<T>::Matrix(int nbRows, int nbColumns, T emptyValue) {
    if (nbRows < 0) {
        nbRows = 0;
    }
    if (nbColumns < 0) {
        nbColumns = 0;
    }
    this->rows = nbRows;
    this->cols = nbColumns;
    this->emptyVal = emptyValue;
    this->data = vector< vector<T> >(nbRows);
    for(int i;i<this->data.size();i++) {
        this->data[i] = vector<T>(nbColumns, emptyValue);
    }
};

template<class T> Matrix<T>::~Matrix() {

};

template<class T> int Matrix<T>::getNbRows() {
    return this->rows;
};

template<class T> int Matrix<T>::getNbColumns() {
    return this->cols;
};

template<class T> T Matrix<T>::getEmptyValue() {
    return this->emptyVal;
};

template<class T> void Matrix<T>::addRow(int rowIndex) throw (IndexOutOfBoundsException) {
    if (rowIndex < 0) {
        throw IndexOutOfBoundsException(rowIndex, 0, false);
    }
    if (rowIndex>this->rows) {
        throw IndexOutOfBoundsException(rowIndex, this->rows, false);
    }
    vector<T> row = vector<T>(this->cols,this->emptyVal);
    typename std::vector<vector<T> >::iterator it;
    it = this->data.begin();
    for(int i = 0;i < rowIndex;i++){
        it++;
    }
    this->data.insert(it,row);
    this->rows ++ ;

};

template<class T> void Matrix<T>::removeRow(int rowIndex) throw (IndexOutOfBoundsException){
    if (rowIndex < 0) {
        throw IndexOutOfBoundsException(rowIndex, 0, false);
    }
    if (rowIndex>this->rows -1) {
        throw IndexOutOfBoundsException(rowIndex, this->rows -1, false);
    } 
    
};

template<class T> T Matrix<T>::getValue(int rowIndex, int colIndex) throw (IndexOutOfBoundsException){
    if(rowIndex < 0){
        throw IndexOutOfBoundsException(rowIndex,0,true);
    }
    if(rowIndex > this->rows){
        throw IndexOutOfBoundsException(rowIndex,this->rows,true);
    }
    if(colIndex < 0){
        throw IndexOutOfBoundsException(colIndex,0,false);
    }
    if(colIndex > this->cols){
        throw IndexOutOfBoundsException(colIndex,this->cols,false);
    }
    if(this->rows == 0){
        throw IndexOutOfBoundsException(rowIndex,rowIndex,true);
    }
    if(this->cols == 0){
        throw IndexOutOfBoundsException(colIndex,colIndex,false);
    }
    return this->data[rowIndex][colIndex];
};
    
template<class T>void Matrix<T>::setValue(int rowIndex, int colIndex, T value) throw (IndexOutOfBoundsException){
    if(rowIndex < 0){
        throw IndexOutOfBoundsException(rowIndex,0,true);
    }
    if(rowIndex > this->rows){
        throw IndexOutOfBoundsException(rowIndex,this->rows,true);
    }
    if(colIndex < 0){
        throw IndexOutOfBoundsException(colIndex,0,false);
    }
    if(colIndex > this->cols){
        throw IndexOutOfBoundsException(colIndex,this->cols,false);
    }
    this->data[rowIndex][colIndex] = value;
};

template<class T> void Matrix<T>::addColumn(int colIndex) throw (IndexOutOfBoundsException){
    if (colIndex < 0) {
        throw IndexOutOfBoundsException(colIndex, 0, false);
    }
    if (colIndex>this->cols) {
        throw IndexOutOfBoundsException(colIndex, this->rows, false);
    } 
    typename std::vector<T>::iterator it;
    for(int i = 0;i < this->rows;i++){
        vector<T> row = data[i];
        it = row.begin();
        for(int j = 0; j < colIndex; j++) {
            it++;
        };
        this->data[i].insert(it,this->emptyVal);
    }
    
    this->cols++ ;
 };
template<class T> void Matrix<T>::removeColumn(int colIndex) throw (IndexOutOfBoundsException){
    
};
#endif	/* MATRIX_H */

