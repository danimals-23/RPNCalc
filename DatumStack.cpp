/*
 * DatumStack.cpp
 * Daniel Peng
 * 23 February 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Implementation of the DatumStack class. All functions are defined here.
 * 
 */


#include "DatumStack.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * name:      DatumStack default constructor
 * purpose:   initializes a DatumStack object
 * arguments: none
 * returns:   none
 * effects:   sets numDatums to 0
 */
DatumStack::DatumStack()
{
    numDatums = 0;
}

/*
 * name:      DatumStack constructor with array and size
 * purpose:   initializes a DatumStack from an array of Datums
 * arguments: a Datum array and its size
 * returns:   none
 * effects:   creates the stack with the array, sets numDatums to size
 */
DatumStack::DatumStack(Datum arr[], int size)
{
    numDatums = size;
    for(int i = 0; i < size; i++){
        stack.push_back(arr[i]);
    }
}


/*
 * name:      DatumStack destructor
 * purpose:   removes all heap associated memory
 * arguments: none
 * returns:   none
 * effects:   uses the clear function, clears the stack
 */
DatumStack::~DatumStack()
{
    clear();
}


/*
 * name:      DatumStack isEmpty function
 * purpose:   checks to see if a given DatumStack is empty
 * arguments: none
 * returns:   true or false
 * effects:   none
 */
bool DatumStack::isEmpty()
{
    return (numDatums == 0);
}


/*
 * name:      DatumStack clear function
 * purpose:   clears the DatumStack
 * arguments: none
 * returns:   none
 * effects:   clears the stack, sets numDatums to 0
 */
void DatumStack::clear()
{
    stack.clear();
    numDatums = 0;
}


/*
 * name:      DatumStack size function
 * purpose:   gets the size of the stack
 * arguments: none
 * returns:   an int representing the size of the stack
 * effects:   none
 */
int DatumStack::size()
{
    return numDatums;
}


/*
 * name:      DatumStack top function
 * purpose:   gets the top of the stack
 * arguments: none
 * returns:   the Datum at the top of stack, runtime_error if empty
 * effects:   none
 */
Datum DatumStack::top()
{
    if(isEmpty()){
        throw runtime_error("empty_stack");
    }
    return stack.back();
}


/*
 * name:      DatumStack pop function
 * purpose:   pops the top of the stack
 * arguments: none
 * returns:   none
 * effects:   removes the top of the stack, throws runtime_error if empty
 */
void DatumStack::pop()
{
    if(isEmpty()){
        throw runtime_error("empty_stack");
    }
    else{
        stack.pop_back();
        numDatums--;
    }
}


/*
 * name:      DatumStack push function
 * purpose:   adds a Datum to the top of the stack
 * arguments: a Datum to be added
 * returns:   none
 * effects:   numDatums increments by 1, and a Datum is added to the stack
 */
void DatumStack::push(Datum elem)
{
    stack.push_back(elem);
    numDatums++;
}