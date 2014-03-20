/* 
 * File:   Test.h
 * Author: sacael
 *
 * Created on 10 mars 2014, 14:07
 */

#ifndef TESTSTATS_H
#define	TESTSTATS_H

#include "matrix.h"
#include <string>
using std::string;
class TestStats {
public:
    TestStats(int planned);
    TestStats(const TestStats& orig);
    virtual ~TestStats();
    void matrixLifeCycleTests(int rows, int cols);
    void deleteMatrixTests(Matrix<float>* m);
    void removeRowsTests(Matrix<float>* m);
    void removeRowTests(Matrix<float>* m, int rowIndex);
    void addRowsTests(Matrix<float>* m, float defVal);
    void addRowTests(Matrix<float>* m, int rowIndex, float defVal);
    void removeColumnsTests(Matrix<float>* m);
    void removeColumnTests(Matrix<float>* m, int colIndex);
    void badAccessTests(Matrix<float>* m);
    void badAccessTest(Matrix<float>* m,int i, int j);
    void addColumnsTests(Matrix<float>* m, float defVal);
    void addColumnTests(Matrix<float>* m, int colIndex, float defVal);
    void setValueTests(Matrix<float>* m);
    void coeffTests(Matrix<float>* m, bool callSetValue, int rowMin, int rowMax, int colMin, int colMax, float expectedValue);
    Matrix<float>* newMatrixTests(int rows, int cols, float defVal);
    void nullPointerTests();
    void printTestStats();
    string printTestStatus(bool expectedEqualsActual);

private:
    int passed;
    int failed;
    int done;
    int planned;
};

#endif	/* TEST_H */

