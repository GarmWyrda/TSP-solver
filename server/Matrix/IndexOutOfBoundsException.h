/* 
 * File:   IndexOutOfBoundsException.h
 * Author: louis
 *
 * Created on March 10, 2014, 2:10 PM
 */

#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define	INDEXOUTOFBOUNDSEXCEPTION_H
#include <iostream>
using std::cout;
using std::endl;

class IndexOutOfBoundsException{
    private:
    int index;
    int bound;
    bool side; //true for horizontal, false for vertical
    
    public:
    IndexOutOfBoundsException(int index, int bound, bool side){
        this->index = index;
        this->bound = bound;
        this->side = side;
    };
    
    void print(){
        cout << "IndexOutOfBoundsException : the index " << index << " violates the bound " << bound;
        if(this->side){
            cout << " horizontally" << endl;
        }
        else{
            cout << " vertically" << endl;
        }
    }
};


#endif	/* INDEXOUTOFBOUNDSEXCEPTION_H */

