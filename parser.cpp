/*
 * parser.cpp
 * Daniel Peng
 * 23 February 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Implementation of the parser class. Contains a single function that reads
 * an rstring.
 * 
 */

#include <iostream>

using namespace std;

/*
 * name:      parser.cpp parseRString function
 * purpose:   parses an input stream, and returns the rstring representation
 * arguments: an input stream
 * returns:   the string inside the curly brackets
 * effects:   essentially parses a user input that represents an rstring.
 *            Continues reading input until all opening brackets are matched,
 *            and returns the final rstring.
 */
std::string parseRString(std::istream &input)
{
    string rstring = "";
    int count = 1;
    string thing;
    while(count > 0 and not input.eof()){
        input >> thing;
        if(thing == "}"){
            count--;
        }
        if(thing == "{"){
            count++;
        }
        rstring +=  " " + thing;
    }
    if(count != 0){
        throw runtime_error("bad rstring");
    }
    else{
        return "{" + rstring;
    }
}