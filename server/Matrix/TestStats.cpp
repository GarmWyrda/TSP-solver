/* 
 * File:   Test.cpp
 * Author: sacael
 * 
 * Created on 10 mars 2014, 14:07
 */

#include "TestStats.h"
#include <iostream>

using namespace std;

TestStats::TestStats(int planned) {
    this->planned = planned;
    this->passed = 0;
    this->failed = 0;
    this->done = 0;
}

TestStats::TestStats(const TestStats& orig) {
}

TestStats::~TestStats() {
}

// Tests relatifs au cycle de vue d'une matrice : création, ajout/suppression de lignes/colonnes, modification de coefficients, destruction
void TestStats::matrixLifeCycleTests(int rows, int cols){
    Matrix<float>* m;
    m = new Matrix<float>(4,5,0);
    float defVal;
    m = this->newMatrixTests(rows, cols, defVal); // Tests relatifs à la création de la matrice
    //cout<<*m<<endl;
    defVal = m->getEmptyValue();
    this->badAccessTests(m); // Tests relatifs à l'utilisation de {get/set}value avec des indices invalides
    this->setValueTests(m); // Tests relatifs à la modification de tous les coefficients
    //cout<<*m<<endl;
    this->addColumnsTests(m, defVal); // Tests relatifs à l'ajout de colonnes
    //cout<<*m<<endl;
    this->removeColumnsTests(m); // Tests relatifs à la suppression de colonnes
    //cout<<*m<<endl;
    this->addRowsTests(m, defVal); // Tests relatifs à l'ajout de lignes
    //cout<<*m<<endl;
    this->removeRowsTests(m); // Tests relatifs à la suppression de lignes
    //cout<<*m<<endl;
    this->deleteMatrixTests(m); // Tests relatifs à la destruction de la matrice
}


// Tests relatifs à la destruction d'une matrice : au début, au milieu, à la fin + cas d'erreur
void TestStats::deleteMatrixTests(Matrix<float>* m){
    cout<<"deleteMatrix doit réussir avec une matrice différente de NULL : "<<endl;
    try{
        delete m;
        cout<<printTestStatus(true)<<endl;
    }
    catch(...){
        cout<<printTestStatus(false)<<endl;
    }
}


// Tests relatifs à la suppression de lignes dans une matrice : au début, au milieu, à la fin + cas d'erreur
void TestStats::removeRowsTests(Matrix<float>* m){
    this->removeRowTests(m,0); // début
    this->removeRowTests(m,m->getNbRows()/2); // milieu
    this->removeRowTests(m,m->getNbRows()-1); // fin
    // cas d'erreur
    this->removeRowTests(m,-1); // avant le début
    this->removeRowTests(m,m->getNbRows()); // après la fin 
}


// Tests relatifs à la suppression d'une ligne dans une matrice
void TestStats::removeRowTests(Matrix<float>* m, int rowIndex){
    bool success;
    int rows;
    rows = m->getNbRows();
    try {
        m->removeRow(rowIndex);
        success = true;
    }
    catch(...){
        success = false;
    }
    if(rowIndex >= rows || rowIndex < 0){
        cout<<"removeRow doit échouer avec l'indice "<<rowIndex<<" : "<<this->printTestStatus(success == false)<<endl;
        cout<<"Le nombre de lignes de la matrice n'a pas changé : "<<this->printTestStatus(rows == m->getNbRows())<<endl;	
    }
    else
    {
        cout<<"removeRow doit réussir avec l'indice "<<rowIndex<<" : "<<this->printTestStatus(success)<<endl;
        cout<<"Le nombre de lignes de la matrice a été décrémenté : "<<this->printTestStatus(rows-1 == m->getNbRows())<<endl;	
    }
}


// Tests relatifs à l'ajout de lignes dans une matrice : au début, au milieu, à la fin + cas d'erreur
void TestStats::addRowsTests(Matrix<float>* m, float defVal){
    this->addRowTests(m,0,defVal); // début
    this->addRowTests(m,m->getNbRows()/2,defVal); // milieu
    this->addRowTests(m,m->getNbRows(),defVal); // fin
    // cas d'erreur
    this->addRowTests(m,-1,defVal); // avant le début
    this->addRowTests(m,m->getNbRows()+1,defVal); // après la fin 		
}


// Tests relatifs à l'ajout d'une ligne dans une matrice
void TestStats::addRowTests(Matrix<float>* m, int rowIndex, float defVal){
    bool success;
    int rows;
    float newVal;
    rows = m->getNbRows();
    try{
        m->addRow(rowIndex);
        success = true;
    }
    catch(...){
        success = false;
    }
    newVal = 42;
    if(rowIndex > rows || rowIndex < 0){
        cout<<"addRow doit échouer avec l'indice "<<rowIndex<<" : "<<this->printTestStatus(success == false)<<endl;
        cout<<"Le nombre de lignes de la matrice n'a pas changé : "<<this->printTestStatus(rows == m->getNbRows())<<endl;
    }
    else
    {
        cout<<"addRow doit réussir avec l'indice "<<rowIndex<<" : "<<this->printTestStatus(success)<<endl;
        cout<<"Le nombre de lignes de la matrice a été incrémenté : "<<this->printTestStatus(rows+1 == m->getNbRows())<<endl;
        cout<<"Une nouvelle ligne est apparue avec la valeur par défaut : "<<endl;
	this->coeffTests(m, false, rowIndex, rowIndex, 0, m->getNbColumns()-1, defVal);
        cout<<"On met la valeur "<<newVal<<" dans la nouvelle ligne et on vérifie que les affectations se sont bien déroulées : "<<endl;
        this->coeffTests(m, true, rowIndex, rowIndex, 0, m->getNbColumns()-1, newVal);			
    }		
}


// Tests relatifs Ã  la suppression de colonnes dans une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
void TestStats::removeColumnsTests(Matrix<float>* m){
    this->removeColumnTests(m,0); // début
    this->removeColumnTests(m,m->getNbColumns()/2); // milieu
    this->removeColumnTests(m,m->getNbColumns()-1); // fin
    // cas d'erreur
    this->removeColumnTests(m,-1); // avant le début
    this->removeColumnTests(m,m->getNbColumns()); // après la fin 
}


// Tests relatifs à la suppression d'une colonne dans une matrice
void TestStats::removeColumnTests(Matrix<float>* m, int colIndex){
    bool success;
    int cols;
    cols = m->getNbColumns();
    try{
        m->removeColumn(colIndex);
        success = true;
    }
    catch(...){
        success = false;
    }
    if(colIndex >= cols || colIndex < 0){
        cout<<"removeColumn doit échouer avec l'indice "<<colIndex<<" : "<<this->printTestStatus(success == false)<<endl;
        cout<<"Le nombre de colonnes de la matrice n'a pas changé : "<<this->printTestStatus(cols == m->getNbColumns())<<endl;	
    }
    else
    {
        cout<<"removeColumn doit réussir avec l'indice "<<colIndex<<" : "<<this->printTestStatus(success)<<endl;
        cout<<"Le nombre de colonnes de la matrice a été décrémenté : "<<this->printTestStatus(cols-1 == m->getNbColumns())<<endl;
    }
}


// Tests relatifs à l'utilisation de {get/set}value avec des indices invalides
void TestStats::badAccessTests(Matrix<float>* m){
    int rows, cols;
    rows = m->getNbRows();
    cols = m->getNbColumns();
    this->badAccessTest(m, -1, -1);
    this->badAccessTest(m, rows/2, -1);
    this->badAccessTest(m, -1, cols/2);
    this->badAccessTest(m, rows/2, cols);
    this->badAccessTest(m, rows, cols/2);
    this->badAccessTest(m, rows, cols);
}

// Tests relatifs à l'utilisation de {get/set}value avec un indice invalide
void TestStats::badAccessTest(Matrix<float>* m,int i, int j){
    bool success;
    try{
        //cout<<*m<<endl<<i<<endl<<j<<endl;
        cout<<"setValue doit échouer sur le coefficient ("<<i<<","<<j<<") : ";
        m->setValue(i, j, 42);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<this->printTestStatus(success == false)<<endl;
    try{
       //cout<<*m<<endl;
        cout<<"getValue doit échouer sur le coefficient ("<<i<<","<<j<<") : ";
        m->getValue(i, j);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<this->printTestStatus(success == false)<<endl;	
}


// Tests relatifs à l'ajout de colonnes dans une matrice : au début, au milieu, à la fin + cas d'erreur
void TestStats::addColumnsTests(Matrix<float>* m, float defVal){
    this->addColumnTests(m,0,defVal); // début
    this->addColumnTests(m,m->getNbColumns()/2,defVal); // milieu
    this->addColumnTests(m,m->getNbColumns(),defVal); // fin
    // cas d'erreur
    this->addColumnTests(m,-1,defVal); // avant le début
    this->addColumnTests(m,m->getNbColumns()+1,defVal); // après la fin 
}


// Tests relatifs à l'ajout d'une colonne dans une matrice
void TestStats::addColumnTests(Matrix<float>* m, int colIndex, float defVal){
    bool success;
    int cols;
    float newVal;
    cols = m->getNbColumns();
    try{
        m->addColumn(colIndex);
        success = true;
    }
    catch(...){
        success = false;
    }
    newVal = 404;
    if(colIndex > cols || colIndex < 0){
        cout<<"addColumn doit échouer avec l'indice "<<colIndex<<" : "<<this->printTestStatus(success == false)<<endl;
        cout<<"Le nombre de colonnes de la matrice n'a pas changé : "<<this->printTestStatus(cols == m->getNbColumns())<<endl;	
    }
    else
    {
        cout<<"addColumn doit réussir avec l'indice "<<colIndex<<" : "<<this->printTestStatus(success)<<endl;
        cout<<"Le nombre de colonnes de la matrice a été incrémenté : "<<this->printTestStatus(cols+1 == m->getNbColumns())<<endl;
        cout<<"Une nouvelle colonne est apparue avec la valeur par défaut : "<<endl;
        this->coeffTests(m, false,  0, m->getNbRows()-1, colIndex, colIndex, defVal);
        cout<<"On met la valeur "<<newVal<<" dans la nouvelle colonne et on vérifie que les affectations se sont bien déroulées : "<<endl;
        this->coeffTests(m, true,  0, m->getNbRows()-1, colIndex, colIndex, newVal);		
    }	
}

// Tests relatifs à la modification de tous les coefficients dans une matrice
void TestStats::setValueTests(Matrix<float>* m){
    int i, j, rows, cols;
    float value, retrievedValue;
    bool success;
    cout<<"Changement de tous les coefficiants de la matrice : "<<endl;
    rows = m->getNbRows();
    cols = m->getNbColumns();
    for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
                    value = 1 + j + cols * i;
                    this->coeffTests(m, true, i, i, j, j, value);
		}	
    }
}


// Tests relatifs à la récupération et/ou la modification d'une partie des coefficients d'une matrice
void TestStats::coeffTests(Matrix<float>* m, bool callSetValue, int rowMin, int rowMax, int colMin, int colMax, float expectedValue){
    float coeff;
    bool success;
    int i, j;
    for(i=rowMin; i<=rowMax; i++){
        for(j=colMin; j<=colMax; j++){
            if(callSetValue){
                cout<<"setValue doit réussir sur le coefficient ("<<i<<","<<j<<") : ";
                try{
                    m->setValue(i, j, expectedValue);
                    success = true;
                }
                catch(...){
                    success = false;
                }
                cout<<this->printTestStatus(success)<<endl;
            }
            coeff = -1;
            cout<<"getValue doit réussir sur le coefficient ("<<i<<","<<j<<") : ";
            try{
                coeff = m->getValue(i, j);
                success = true;
            }
            catch(...){
                success = false;
            }
            cout<<this->printTestStatus(success)<<endl;
            cout<<"getValue doit modifier la valeur du flottant fourni à "<<expectedValue<<" : "<<this->printTestStatus(coeff == expectedValue)<<endl;
        }
    }	
}

// Tests relatifs à la céation d'une matrice
Matrix<float>* TestStats::newMatrixTests(int rows, int cols, float defVal){
    Matrix<float>* m;
    float coeff;
    bool success;
    coeff = -1;
    try{
        m = new Matrix<float>(rows, cols, defVal);
    }
    catch(...){
        m = NULL;
    }
        if(rows >= 0 && cols >= 0){
            cout<<"L'appel à newMatrix avec les dimenstions "<<rows<<" et "<<cols<<" ne doit pas renvoyer NULL : "<<this->printTestStatus(m != NULL)<<endl;
            cout<<"getRows doit retourner "<<rows<<" : "<<this->printTestStatus(m->getNbRows() == rows)<<endl;
            cout<<"getCols doit retourner "<<cols<<" : "<<this->printTestStatus(m->getNbColumns() == cols)<<endl;
            try{
                coeff = m->getEmptyValue();
                success = true;
            }
            catch(...){
                success = false;
            }
            cout<<"getEmptyValue doit réussir : "<<this->printTestStatus(success)<<endl;
            cout<<"getEmptyValue doit modifier la valeur du flottant fourni à "<<defVal<<" : "<<this->printTestStatus(coeff == defVal)<<endl;
            cout<<"Tous les coefficients de la matrice doivent être égaux à la valeur par défaut : "<<endl;
            this->coeffTests(m, 0, false,  rows-1, 0, cols-1, defVal);
        }
        else
        {
            cout<<"L'appel à newMatrix avec les dimenstions "<<rows<<" et "<<cols<<" doit renvoyer NULL : "<<this->printTestStatus(m == NULL)<<endl;	
        }
        return m;
}

// Cas d'erreurs avec pointeur NULL
void TestStats::nullPointerTests(){
    Matrix<float>* m;
    bool success;
    float coeff;
    m = nullptr;
    coeff = 42;
    cout<<"Toutes les opérations doivent échouer avec un pointeur NULL : "<<endl;
    cout<<"getColumns : "<<this->printTestStatus(m->getNbColumns() == -1)<<endl;
    cout<<"getRows : "<<this->printTestStatus(m->getNbRows() == -1)<<endl;
    try{
        delete m;
        cout<<printTestStatus(false)<<endl;
    }
    catch(...){
        cout<<printTestStatus(true)<<endl;
    }
    try{
        coeff = m->getEmptyValue();
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"getEmptyValue : "<<this->printTestStatus(success)<<endl;
    cout<<"Le flottant fourni n'a pas été modifié par getEmptyValue : "<<this->printTestStatus(coeff == 42)<<endl;
    try{
        coeff = m->getValue(0, 0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"getValue : "<<this->printTestStatus(success)<<endl;
    cout<<"Le flottant fourni n'a pas été modifié par getValue : "<<this->printTestStatus(coeff == 42)<<endl;
    try{
        m->setValue(0, 0, 0.0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"setValue : "<<this->printTestStatus(success)<<endl;
    try{
        m->addRow(0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"addRow : "<<this->printTestStatus(success)<<endl;
    try{
        m->removeRow(0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"removeRow : "<<this->printTestStatus(success)<<endl;
    try{
        m->addColumn(0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"addColumn : "<<this->printTestStatus(success)<<endl;
    try{
        m->removeColumn(0);
        success = true;
    }
    catch(...){
        success = false;
    }
    cout<<"removeColumn : "<<this->printTestStatus(success)<<endl;
}


// ======================= STATISTIQUES SUR LES TESTS ===============================
void TestStats::printTestStats(){
        cout<<"****** Test stats *******"<<endl;
        cout<<"Planned : "<<this->planned<<endl;
        cout<<"Passed : "<<this->passed<<endl;
        cout<<"Failed : "<<this->failed<<endl;
        cout<<"Missed : "<<(this->planned - this->done)<<endl;	
    
}

string TestStats::printTestStatus(bool expectedEqualsActual){
    this->done = this->done + 1;
    if(expectedEqualsActual) {
        this->passed = this->passed + 1;
                return "PASSED";
    }
    else
    {
        this->failed = this->failed + 1;
        return "FAILED";
    }
}