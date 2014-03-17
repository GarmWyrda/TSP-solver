#include "matrix.h"

void printTestStatus (bool test){
    if(test){
        cout << "PASSED" <<endl;
    }
    else{
        cout << "FAILED" <<endl;
    }
}

int main(){
    Matrix<int> testMatrix = Matrix<int>(0,0,0);
    
    //Test Getters
    if(testMatrix.getNbRows() == 0) {
        cout<<"getNbRows OK"<<endl ;
    }else {
        cout<<"getNbRows not OK"<<endl;
    }
    
    if(testMatrix.getNbColumns() == 0) {
        cout<<"getNbColumns OK"<<endl ;
    }else {
        cout<<"getNbColumns not OK"<<endl;
    }
    
    if(testMatrix.getEmptyValue() == 0) {
        cout<<"getEmptyValue OK"<<endl ;
    }else {
        cout<<"getEmptyValue not OK"<<endl;
    }
    testMatrix.addRow(0);
    try{
      testMatrix.addRow(-1);  
    }
    catch(IndexOutOfBoundsException ex){
        cout<<"Exception correctly thrown"<<endl ;
    }
    try{
      testMatrix.addRow(5);  
    }
    catch(IndexOutOfBoundsException ex){
        cout<<"Exception correctly thrown"<<endl ;
    }
    testMatrix.addRow(1);
     if(testMatrix.getNbRows() == 2) {
        cout<<"addRow OK"<<endl ;
    }else {
        cout<<"addRow not OK"<<endl;
    }
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
    testMatrix.addColumn(1);
     if(testMatrix.getNbColumns() == 2) {
        cout<<"addColumn OK"<<endl ;
    }else {
        cout<<"addCommn not OK"<<endl;
    }

    
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
}
