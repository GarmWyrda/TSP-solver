#include "matrix.h"
#include "TestStats.h"
#include "../Little/Little.h"
/***Statistiques sur les tests***/
/*
struct testStats{
    int passed;
    int failed;
    int done;
    int planned;
};

void printTestStats (testStats &stats){
    cout << "Planned : " << stats->planned << endl;
    cout << "Failed : " << stats->failed << endl;
    cout << "Passed : " << stats->passed << endl;
    cout << "Missed : " << stats->planned-stats->done << endl;
}

void printTestStatus (bool test, testStats &stats){
    stats->done++;
    if(test){
        stats->passed++;
        cout << "PASSED" << endl;
    }
    else{
        stats->failed++;
        cout << "FAILED" << endl;
    }
}
void coeffTests(Matrix<int>* m,bool callSetValue, int rowMin, int rowMax, int colMin, int colMax, int expectedValue,testStats& stats){
    
}

Matrix<int>* newMatrixTests(int rows, int cols, int defVal, testStats &stats){
    int coef = -1;
    Matrix<int>* m = new Matrix<int>(rows,cols,defVal);
    
    
    if(rows >= 0 && cols >=0){
        printTestStatus(m != NULL,stats);
        int retrievedRows = m->getNbRows();
        int retrievedCols = m->getNbColumns();
        printTestStatus(m->getNbRows() == rows, stats);
        printTestStatus(m->getNbColumns() == cols, stats);
        printTestStatus(m->getEmptyValue() == defVal, stats);
        printTestStatus(m->getEmptyValue() == defVal, stats);
        coeffTests(m,false,0,rows-1,0,cols-1,defVal,stats);
    }
    else{
        printTestStatus(m == NULL,stats);
    }
    return m;
}

void deleteMatrixTests(Matrix<int>* m, testStats stats){
    bool success;
    
}
*/

/*int main2(){
    testStats stats;
    stats->failed = 0;
    stats->passed = 0;
    stats->done = 0;
    stats->planned = 429;
    

    Matrix<int> testMatrix = Matrix<int>(0,0,0);
    
    //Test Getters

    printTestStatus(testMatrix.getNbRows() == 0);
    printTestStatus(testMatrix.getNbColumns() == 0);
    printTestStatus(testMatrix.getEmptyValue() == 0);
 
    
    testMatrix.addRow(0);
    try{
      testMatrix.addRow(-1);  
    }
    catch(IndexOutOfBoundsException ex){
        printTestStatus(true) ;
    }
    try{
      testMatrix.addRow(5);  
    }
    catch(IndexOutOfBoundsException ex){
        printTestStatus(true);
    }
    testMatrix.addRow(1);
    cout<<"toussa"<<endl;
    testMatrix.addColumn(0);
    cout<<"pfd "<<endl;
    try{
      testMatrix.addColumn(-1);  
    }
    catch(IndexOutOfBoundsException ex){
        cout<<"Exception correctly thrown"<<endl ;
    }
    try{
      testMatrix.addColumn(5);  
    }
    catch(IndexOutOfBoundsException ex){
        cout<<"Exception correctly thrown"<<endl ;
    }
    cout<<testMatrix.getNbColumns();
    testMatrix.addColumn(1);
    cout<<"berthe"<<endl;
     if(testMatrix.getNbColumns() == 2) {
        cout<<"addColumn OK"<<endl ;
    }else {
        cout<<"addCommn not OK"<<endl;
    }      
    printTestStatus(testMatrix.getNbRows() == 2);
  
    try{
        testMatrix.getValue(0,0);
    }
    catch(IndexOutOfBoundsException ex){
        printTestStatus(true);
    }
    
    testMatrix.addColumn(0);
    printTestStatus(testMatrix.getValue(0,0) == 0);
    testMatrix.setValue(0,0,5);
    printTestStatus(testMatrix.getValue(0,0) == 5);
};*/

int main(){
    
    TestStats* stats = new TestStats(415);

    stats->newMatrixTests(2,-1,0);
    stats->newMatrixTests(-1,3,0);
    stats->newMatrixTests(-1,-1,0);

    stats->matrixLifeCycleTests(0,0);
    stats->matrixLifeCycleTests(2,0);
    stats->matrixLifeCycleTests(0,3);
    stats->matrixLifeCycleTests(2,3);

    stats->printTestStats();
    
    delete stats;

}
