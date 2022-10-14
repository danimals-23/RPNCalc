/*
 * DatumStack.h
 * Daniel Peng
 * 23 February 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Class declaration for the DatumStack class.
 * 
 */

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include "Datum.h"
#include <iostream>
#include <vector>


class DatumStack {
public:
    DatumStack();
    DatumStack(Datum arr[], int size);
    ~DatumStack();
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum elem);



private:
    std::vector<Datum> stack;
    int numDatums;
};



#endif