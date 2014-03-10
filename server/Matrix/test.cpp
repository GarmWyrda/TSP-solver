#include "matrix.h"

int main(){
    Matrix<int> testMatrix = Matrix<int>(0,0,0);
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
    testMatrix.addRow(5);
    testMatrix.addRow(1);
     if(testMatrix.getNbRows() == 2) {
        cout<<"addRow OK"<<endl ;
    }else {
        cout<<"addRow not OK"<<endl;
    }
}
