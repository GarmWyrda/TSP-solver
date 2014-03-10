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
    vector< vector<T*> > data;

public:

    // -------------- interdit de modifier cette partie -------------- //
    Matrix(int nbRows, int nbColumns, T emptyValue); //done

    T getEmptyValue(); //done

    int getNbRows(); // done
    void addRow(int rowIndex) throw (IndexOutOfBoundsException);
    void removeRow(int rowIndex) throw (IndexOutOfBoundsException);

    int getNbColumns(); // done
    void addColumn(int colIndex) throw (IndexOutOfBoundsException);
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
    this->data = vector< vector<T*> >(nbRows);
    for(int i;i<this->data.size();i++) {
        this->data[i] = vector<T*>(nbColumns, NULL);
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
        IndexOutOfBoundsException(rowIndex, 0, false);
    }
    if (rowIndex>this->rows) {
        IndexOutOfBoundsException(rowIndex, this->rows, false);
    }
    vector<T*> row = vector<T*>(this->cols,NULL);
    typename std::vector<vector<T*> >::iterator it;
    it = this->data.begin();
    for(int i = 0;i < rowIndex;i++){
        it++;
    }
    row.assign(this->cols-1,NULL);
    this->data.insert(it,row);
    this->rows ++ ;

};
#endif	/* MATRIX_H */

