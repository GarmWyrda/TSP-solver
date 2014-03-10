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
        vector<vector<T>> data;

    public :

    // -------------- interdit de modifier cette partie -------------- //
    Matrix(int nbRows, int nbColumns, T emptyValue);

    T getEmptyValue();

    int getNbRows();
    void addRow(int rowIndex) throw(IndexOutOfBoundsException);
    void removeRow(int rowIndex) throw(IndexOutOfBoundsException);

    int getNbColumns();
    void addColumn(int colIndex) throw(IndexOutOfBoundsException);
    void removeColumn(int colIndex) throw(IndexOutOfBoundsException);

    T getValue(int rowIndex, int colIndex) throw(IndexOutOfBoundsException);
    void setValue(int rowIndex, int colIndex, T value) throw(IndexOutOfBoundsException);

    ~Matrix();
    // --------------------------------------------------------------- //

};


#endif	/* MATRIX_H */

