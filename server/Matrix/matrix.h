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
        vector<vector<T>*> data;

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
template<class T> int Matrix <T>:: getNbRows(){
    return this->rows;
};
template<class T> int Matrix <T>:: getNbColumns(){
    return this->cols;
};
template<class T> int Matrix <T>:: getEmptyValue(){
    return this->emptyVal;
};

#endif	/* MATRIX_H */

