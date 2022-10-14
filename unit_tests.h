/*
 *  unit_tests.h
 *  Daniel Peng
 *  22 February 2022
 *
 *  CS 15 Proj2: CalcYouLater
 *
 *  Uses Matt Russell's unit_test framework to test MetroSim and its classes
 *
 */

#include "DatumStack.h"
#include "RPNCalc.h"
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


// // ParseRString function prototype, used for testing parser.cpp
// std::string parseRString(std::istream &input)
// {
//     string rstring = "";
//     int count = 1;
//     string thing;
//     while(count > 0 and not input.eof()){
//         input >> thing;
//         if(thing == "}"){
//             count--;
//         }
//         if(thing == "{"){
//             count++;
//         }
//         rstring +=  " " + thing;
//     }
//     if(count != 0){
//         throw runtime_error("bad rstring");
//     }
//     else{
//         return "{" + rstring;
//     }
// }

// Tests the default constructor and destructor of DatumStack
void datumStackConstructor1()
{
    DatumStack l;
}

// Tests the second DatumStack constructor()
void datumStackConstructor2()
{
    Datum one(1);
    Datum two(2);
    Datum my_arr[] = {one, two};
    DatumStack l(my_arr, 2);
}

// Tests the isEmpty function on a datumStack that is empty and one that's not
void datumStackEmpty()
{
    DatumStack l;
    assert(l.isEmpty());
    Datum one(1);
    Datum two(2);
    Datum my_arr[] = {one, two};
    DatumStack l2(my_arr, 2);
    assert(!l2.isEmpty());
}

// Tests the size function on a datumStack of size 2
void datumStackSize()
{
    Datum one(1);
    Datum two(2);
    Datum my_arr[] = {one, two};
    DatumStack l(my_arr, 2);
    assert(l.size() == 2);
}

// Tests the size function on a datumStack of size 0
void datumStackSizeEmpty()
{
    DatumStack l;
    assert(l.size() == 0);
}

// Tests the clear function on a datumStack of size 3
void datumStackClear1()
{
    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum my_arr[] = {one, two, three};
    DatumStack l(my_arr, 3);
    assert(l.size() == 3);
    l.clear();
    assert(l.size() == 0);
}

// Tests the clear function on a datumStack of size 0
void datumStackClear2()
{
    DatumStack l;
    assert(l.size() == 0);
    l.clear();
    assert(l.size() == 0);
}


// Tests the top function which should return the last element of the stack
void datumStackTop()
{
    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum my_arr[] = {one, two, three};
    DatumStack l(my_arr, 3);

    assert(l.top() == three);
}

// Tests the top function on an empty DatumStack, should throw runtime_error
void datumStackTopEmpty()
{
    DatumStack l;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        l.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// Tests the pop function on a DatumStack of size 3
// Asserts the size before popping, and again after popping.
void datumStackPop()
{
    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum my_arr[] = {one, two, three};
    DatumStack l(my_arr, 3);

    assert(l.size() == 3);
    assert(l.top() == three);
    l.pop();
    assert(l.size() == 2);
    assert(l.top() == two);
}

// Tests the pop function on an empty DatumStack, should return runtime_error
void datumStackPopEmpty()
{
    DatumStack l;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        l.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// Tests the push function on a DatumStack of size 3
// Asserts the size before pushing, and again after pushing.
void datumStackPush()
{
    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum my_arr[] = {one, two, three};
    DatumStack l(my_arr, 3);
    
    assert(l.size() == 3);
    assert(l.top() == three);

    Datum four(4);
    l.push(four);

    assert(l.size() == 4);
    assert(l.top() == four);
}

// Tests the push function on an empty datumStack.
void datumStackPushEmpty()
{
    DatumStack l;
    assert(l.isEmpty());
    Datum one(1);
    l.push(one);
    assert(l.size() == 1);
}


/*
 * BELOW ARE COMMENTED-OUT UNIT TESTS FOR PARSER.CPP
 *
 * The tests below were used in week 1 when testing parseRString(). They have
 * been commented out, as parser.cpp is not included in week 2.
 * 
 */


// // Tests a simple rString using input from a text file
// void parseRStringSimple()
// {
//     ifstream input;
//     input.open("parseRStringSimple.txt");
//     std::string result = parseRString(input);
//     assert(result == "{ 1 2 3 4 5 }");
//     input.close();
// }

// // Tests a bad rstring which should cause the parseRString function to throw
// // a runtime error.
// void parseRStringFail()
// {
//     ifstream input;
//     input.open("parseRStringFail.txt");
//     bool runtime_error_thrown = false;
//     std::string error_message = "";
//     try {
//         string result = parseRString(input);
//     }
//     catch (const std::runtime_error &e) {
//         runtime_error_thrown = true;
//         error_message = e.what();
//     }
//     assert(runtime_error_thrown);
//     assert(error_message == "bad rstring");

//     input.close();
// }

// // Tests the first rstring example from the project specs to make sure that
// // parseRString is working correctly.
// void parseRStringExample1()
// {
//     ifstream input;
//     input.open("parseRStringExample1.txt");
//     std::string result = parseRString(input);
//     assert(result == "{ 1 2 + }");
//     input.close();
// }

// // Tests the second rstring example from the project specs to make sure that
// // parseRString is working correctly.
// void parseRStringExample2()
// {
//     ifstream input;
//     input.open("parseRStringExample2.txt");
//     std::string result = parseRString(input);
//     assert(result == "{ 1 { 4 2 / } / }");
//     input.close();
// }

// // Tests the parseRString function using stringstream
// void parseRStringWorks()
// {
//     stringstream input;
//     input << "1 2 + }";
//     std::string result = parseRString(input);
//     assert(result == "{ 1 2 + }");
// }

// // Tests the parseRString function when a bad input is given
// void parseRStringFail2()
// {
//     stringstream input;
//     input << "1 { 2 + }";
//     bool runtime_error_thrown = false;
//     std::string error_message = "";
//     try {
//         string result = parseRString(input);
//     }
//     catch (const std::runtime_error &e) {
//         runtime_error_thrown = true;
//         error_message = e.what();
//     }
//     assert(runtime_error_thrown);
//     assert(error_message == "bad rstring");
// }


// tests to make sure that inputting #t as a command will push a datum with
// the boolean 'true' to the stack
// This test also tests the print function to cout
// void pushBooleanTrue(){
//     RPNCalc *myCalc = new RPNCalc();
//     stringstream commands;
//     commands << "#t print";

//     myCalc->runHelper(commands);
//     delete myCalc;
// }

// void pushBooleanFalse(){
//     RPNCalc *myCalc = new RPNCalc();
//     stringstream commands;
//     commands << "#f print";

//     myCalc->runHelper(commands);
//     delete myCalc;
// }


// tests that the removeBrackets function is working correctly
// takes in an rstring { 1 2 + } and should return the string without brackets
void removeBracketsEquation(){
    string eq = "{ 1 2 + }";
    string result = eq.substr(2, eq.length() - 4);
    assert(result == "1 2 +");
}

// tests that the removeBrackets function is working for files as well
void removeBracketsFile(){
    string filename = "{ add.cylc }";
    string result = filename.substr(2, filename.length() - 4);
    assert(result == "add.cylc");
}