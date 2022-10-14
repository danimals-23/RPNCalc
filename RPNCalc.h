/*
 * RPNCalc.h
 * Daniel Peng
 * 23 February 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Class declaration for the RPNCalc class.
 * 
 */

#ifndef _RPNCALC_H_
#define _RPNCALC_H_

#include "DatumStack.h"
#include <iostream>
#include <vector>


class RPNCalc{
public:
    RPNCalc();
    void run();
    ~RPNCalc();

private:
    void runHelper(std::istream &stream);
    bool got_int(std::string s, int *resultp);
    void opposite();
    void print(std::ostream &stream);
    void drop();
    void duplicate();
    void swap();

    bool isOperator(std::string str);
    void doOperation(std::string str);
    void add();
    void subtract();
    void multiply();
    void divide();
    void mod();

    bool isComparison(std::string str);
    void doComparison(std::string str);
    void lessThan();
    void greaterThan();
    void lessOrEqual();
    void greaterOrEqual();
    void equals();

    std::string parseRString(std::istream &input);
    void runExec();
    void runRstring(Datum a);
    std::string removeBrackets(std::string input);
    void runFile();
    void runIf();
    void runIfHelper(Datum trueCase, Datum falseCase, Datum testCondition);

    DatumStack calcStack;
};
#endif