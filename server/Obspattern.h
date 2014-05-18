/* 
 * File:   Obspattern.h
 * Author: louis
 *
 * Created on May 17, 2014, 4:50 PM
 */

#ifndef OBSPATTERN_H
#define	OBSPATTERN_H

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include "Way.h"


typedef int Info;

class Observable;

class Observateur
{
 protected:
    std::list<Observable*> m_list;
   typedef std::list<Observable*>::iterator iterator; 
   typedef std::list<Observable*>::const_iterator const_iterator;
   virtual ~Observateur() = 0;
 public:
    virtual void Update(Observable* observable);

    void AddObs(Observable* obs);
    void DelObs(Observable* obs);
};

class Observable
{
    std::list<Observateur*> m_list;

   typedef std::list<Observateur*>::iterator iterator; 
   typedef std::list<Observateur*>::const_iterator const_iterator;

 public:
    void AddObs( Observateur* obs);
    void DelObs(Observateur* obs);
        virtual Way Statut(void)=0;
    virtual ~Observable();
 protected:
    void Notify(void);

};


#endif	/* OBSPATTERN_H */

