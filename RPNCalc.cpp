/*
 * RPNCalc.cpp
 * Daniel Peng
 * 23 February 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * Implementation for the RPNCalc class. This file contains all the functions
 * and their implementation in the RPNCalc class.
 * 
 */

#include "RPNCalc.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

/*
 * name:      RPNCalc.cpp default constructor
 * purpose:   initializes a new RPNCalc
 * arguments: none
 * returns:   none
 * effects:   initializes a new RPNCalc
 */
RPNCalc::RPNCalc()
{
    
}

/*
 * name:      RPNCalc.cpp destructor
 * purpose:   recycles all memory declared on the heap
 * arguments: none
 * returns:   none
 * effects:   clears the stack, just to make sure that no memory is left
 *            on the heap (though, DatumStack's own destructor calls
 *            clear() as well. this is just a safeguard).
 */
RPNCalc::~RPNCalc()
{
    calcStack.clear();
}

/*
 * name:      RPNCalc.cpp run function
 * purpose:   runs the helper function for the user input command loop
 * arguments: none
 * returns:   none
 * effects:   runs the helper command loop function, prints "Thank you for
 *            using CalcYouLater." once the helper function ends.
 */
void RPNCalc::run()
{
    runHelper(std::cin);
    cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name:      RPNCalc.cpp run helper function
 * purpose:   runs a command loop that takes in an input stream object
 * arguments: an istream object
 * returns:   none
 * effects:   continues running user input until the user inputs "quit", or
 *            if the input file has reached the end.
 */
void RPNCalc::runHelper(std::istream &stream)
{
    string input;
    int num;
    stream >> input; //continues reading in input
    while(input != "quit" and not stream.fail()){
        if(got_int(input, &num)){
            calcStack.push(Datum(num)); //pushes datum containing integer
        }
        else if(input == "#t"){
            calcStack.push(Datum(true)); //pushes datum containing true
        }
        else if(input == "#f"){
            calcStack.push(Datum(false)); //pushes datum containing false
        }
        else if(input == "not"){
            opposite(); //calls opposite function
        }
        else if(input == "print"){
            print(cout); //calls print function to cout
        }
        else if(input == "clear"){
            calcStack.clear(); //clears calcStack
        }
        else if(input == "drop"){
            drop(); //pops the top datum
        }
        else if(input == "dup"){
            duplicate(); //duplicates the top datum
        }
        else if(input == "swap"){
            swap(); //swaps the top two datums
        }
        else if(isOperator(input)){
            doOperation(input); //runs an operator on the top two datums
        }
        else if(isComparison(input)){
            doComparison(input); //runs a comparison on the top two datums
        }
        else if(input == "{"){ //pushes an rstring to the top of the stack
            calcStack.push(Datum(parseRString(stream)));
        }
        else if(input == "exec"){
            runExec(); //executes the rstring
        }
        else if(input == "file"){
            runFile(); //runs a file
        }
        else if(input == "if"){
            runIf(); //runs the if command
        }
        else{ 
            //if none of the commands above were called, then print to cerr
            std::cerr << input + ": unimplemented\n";
        }
        stream >> input;
    }
}

/*
 * name:      RPNCalc.cpp got_int function
 * purpose:   checks to see if a string is representing an integer
 * arguments: a string, and an integer pointer to the resulting int
 * returns:   a boolean value
 * effects:   returns if a given string is a number/integer
 */
bool RPNCalc::got_int(std::string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name:      RPNCalc.cpp opposite function
 * purpose:   gets a boolean at the top of the stack and replaces it with the
 *            opposite value.
 * arguments: none
 * returns:   none
 * effects:   pops a boolean off the stack, pushes the opposite boolean back
 *            on the top.
 */
void RPNCalc::opposite()
{
    bool result;
    try{
        Datum a = calcStack.top();
        calcStack.pop();
        result = a.getBool();
        calcStack.push(Datum(not result));
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp print function
 * purpose:   prints the string representation of the datum at the top of the
 *            stack
 * arguments: an output stream to be printed to
 * returns:   none
 * effects:   prints the datum at the top of the stack to an output stream
 */
void RPNCalc::print(std::ostream &stream)
{
    try{
        stream << calcStack.top().toString() << endl;
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp drop function
 * purpose:   pops the datum at the top of the calculator's stack
 * arguments: none
 * returns:   none
 * effects:   removes the datum at the top of the stack, throws an empty stack
 *            error if the stack is empty.
 */
void RPNCalc::drop()
{
    try{
        calcStack.pop();
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp duplicate function
 * purpose:   duplicates the datum at the top of the calculator's stack
 * arguments: none
 * returns:   none
 * effects:   duplicates the datum at the top of the stack, throws an empty
 *            stack error if the stack is empty.
 */
void RPNCalc::duplicate()
{
    try{
        Datum dup = calcStack.top();
        calcStack.push(dup);
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp swap function
 * purpose:   swaps the top two datums at the top of the stack
 * arguments: none
 * returns:   none
 * effects:   swaps the top two datums on the calculator stack, throws an
 *            empty stack error if the stack is empty.
 */
void RPNCalc::swap()
{
    try{
        Datum a = calcStack.top();
        calcStack.pop();
        Datum b = calcStack.top();
        calcStack.pop();
        calcStack.push(a);
        calcStack.push(b);
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp isOperator function
 * purpose:   checks to see if a given string is a binary operator, such as
 *            +, -, *, /, or 'mod'
 * arguments: a string
 * returns:   a boolean
 * effects:   checks to see if a string is equal to one of the given binary
 *            operators above.
 */
bool RPNCalc::isOperator(string str)
{
    return (str == "+" or str == "-" or str == "*" or str == "/" 
            or str == "mod");
}

/*
 * name:      RPNCalc.cpp isComparison function
 * purpose:   checks to see if a given string is a comparison operator, such as
 *            <, >, <=, >=, ==
 * arguments: a string
 * returns:   a boolean
 * effects:   checks to see if a string is equal to one of the given comparison
 *            operators above.
 */
bool RPNCalc::isComparison(string str)
{
    return (str == "<" or str == ">" or str == "<=" or str == ">="
            or str == "==");
}

/*
 * name:      RPNCalc.cpp doOperation function
 * purpose:   based on a given binary operator, applies the binary operation
 *            to two datums
 * arguments: a string
 * returns:   none
 * effects:   uses many helper functions; pops two datums off the stack, and
 *            applies a given operation to them. Pushes the resulting value
 *            back to the top of the stack
 */
void RPNCalc::doOperation(string str)
{
    try{
        if(str == "+"){
            add();
        }
        else if(str == "-"){
            subtract();
        }
        else if(str == "*"){
            multiply();
        }
        else if(str == "/"){
            divide();
        }
        else{
            mod();
        }
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp add function
 * purpose:   pops two datums off the stack and adds their values. Pushes
 *            datum with result back to the stack.
 * arguments: none
 * returns:   none
 * effects:   adds the values from two datums and pushes a new datum
 *            containing the result back to the stack. Assumes the two datums
 *            hold integers, and throws error otherwise.
 */
void RPNCalc::add(){
    Datum first = calcStack.top();
    calcStack.pop();
    Datum second = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    int result = (a + b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp subtract function
 * purpose:   pops two datums off the stack and subtracts their values. Pushes
 *            datum with result back to the stack.
 * arguments: none
 * returns:   none
 * effects:   subtracts the values from two datums and pushes a new datum
 *            containing the result back to the stack. Assumes the two datums
 *            hold integers, and throws error otherwise.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the first datum popped will be subtracted from
 *            the second datum popped.
 */
void RPNCalc::subtract(){
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    int result = (a - b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp multiply function
 * purpose:   pops two datums off the stack and multiplies their values. Pushes
 *            datum with result back to the stack.
 * arguments: none
 * returns:   none
 * effects:   multiplies the values from two datums and pushes a new datum
 *            containing the result back to the stack. Assumes the two datums
 *            hold integers, and throws error otherwise.
 *
 */
void RPNCalc::multiply(){
    Datum first = calcStack.top();
    calcStack.pop();
    Datum second = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    int result = (a * b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp divide function
 * purpose:   pops two datums off the stack and divides their values. Pushes
 *            datum with result back to the stack.
 * arguments: none
 * returns:   none
 * effects:   divides the values from two datums and pushes a new datum
 *            containing the result back to the stack. Assumes the two datums
 *            hold integers, and throws error otherwise. Throws an error if
 *            0 is a divisor.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the first datum popped will be divided from
 *            the second datum popped.
 */
void RPNCalc::divide(){
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();
    if(b == 0){
        cerr << "Error: division by 0.\n";
    }
    else{
        int result = (a / b);
        calcStack.push(Datum(result));
    }
}

/*
 * name:      RPNCalc.cpp mod function
 * purpose:   pops two datums off the stack and finds the mod of their values.
 *            Pushes datum with result back to the stack.
 * arguments: none
 * returns:   none
 * effects:   mods the values from two datums and pushes a new datum
 *            containing the result back to the stack. Assumes the two datums
 *            hold integers, and throws error otherwise. Throws an error if
 *            mod by 0 is called.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the first datum popped will be divided from
 *            the second datum popped.
 */
void RPNCalc::mod(){
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();
    
    if(b == 0){
        cerr << "Error: division by 0.\n";
    }
    else{
        int result = (a % b);
        calcStack.push(Datum(result));
    }
}

/*
 * name:      RPNCalc.cpp doOperation function
 * purpose:   based on a given binary operator, applies the comparison to two
 *            datums
 * arguments: a string
 * returns:   none
 * effects:   uses many helper functions; pops two datums off the stack, and
 *            applies a given operation to them. Pushes the resulting value
 *            back to the top of the stack
 */
void RPNCalc::doComparison(string str)
{
    try{
        if(str == "<"){
            lessThan();
        }
        else if(str == ">"){
            greaterThan();
        }
        else if(str == "<="){
            lessOrEqual();
        }
        else if(str == ">="){
            greaterOrEqual();
        }
        else{
            equals();
        }
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp lessThan function
 * purpose:   pops two datums off the stack and compares their values. Pushes
 *            datum with a boolean result to the stack.
 * arguments: none
 * returns:   none
 * effects:   compares the values of two datums from the stack. Returns true
 *            or false, depending on if the second datum is less than the
 *            first.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the second value popped will be compared to the
 *            first value popped. i.e: 
 *                  1 2 < pushes a datum with #t
 *                  2 1 < pushes a datum with #f
 */
void RPNCalc::lessThan()
{
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    bool result = (a < b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp greaterThan function
 * purpose:   pops two datums off the stack and compares their values. Pushes
 *            datum with a boolean result to the stack.
 * arguments: none
 * returns:   none
 * effects:   compares the values of two datums from the stack. Returns true
 *            or false, depending on if the second datum is greater than the
 *            first.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the second value popped will be compared to the
 *            first value popped. i.e: 
 *                  1 2 > pushes a datum with #f
 *                  2 1 > pushes a datum with #t
 */
void RPNCalc::greaterThan()
{
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    bool result = (a > b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp lessOrEqual function
 * purpose:   pops two datums off the stack and compares their values. Pushes
 *            datum with a boolean result to the stack.
 * arguments: none
 * returns:   none
 * effects:   compares the values of two datums from the stack. Returns true
 *            or false, depending on if the second datum is less than or equal
 *            to the first.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the second value popped will be compared to the
 *            first value popped. i.e: 
 *                  1 2 <= pushes a datum with #t
 *                  2 1 <= pushes a datum with #f
 */
void RPNCalc::lessOrEqual()
{
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    bool result = (a <= b);
    calcStack.push(Datum(result));
}

/*
 * name:      RPNCalc.cpp greaterOrEqual function
 * purpose:   pops two datums off the stack and compares their values. Pushes
 *            datum with a boolean result to the stack.
 * arguments: none
 * returns:   none
 * effects:   compares the values of two datums from the stack. Returns true
 *            or false, depending on if the second datum is greater than or
 *            equal to the first.
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the second value popped will be compared to the
 *            first value popped. i.e: 
 *                  1 2 >= pushes a datum with #f
 *                  2 1 >= pushes a datum with #t
 */
void RPNCalc::greaterOrEqual()
{
    Datum second = calcStack.top();
    calcStack.pop();
    Datum first = calcStack.top();
    calcStack.pop();

    int b = second.getInt();
    int a = first.getInt();

    bool result = (a >= b);
    calcStack.push(Datum(result));
}


/*
 * name:      RPNCalc.cpp equals function
 * purpose:   pops two datums off the stack and compares their values. Pushes
 *            datum with a boolean result to the stack.
 * arguments: none
 * returns:   none
 * effects:   compares the values of two datums from the stack. Returns true
 *            or false, depending on if the second datum is equal to the first
 *            
 *            Note: because this is an implementation of an RPN calculator,
 *            the value of the second value popped will be compared to the
 *            first value popped. i.e: 
 *                  1 1 == pushes a datum with #t
 *                  2 1 == pushes a datum with #f
 *                  #t #t == pushes a datum with #t
 */
void RPNCalc::equals()
{
    Datum b = calcStack.top();
    calcStack.pop();
    Datum a = calcStack.top();
    calcStack.pop();

    if(a.isBool() and b.isBool()){
        bool result = (a.getBool() == b.getBool());
        calcStack.push(Datum(result));
    }
    else if(a.isInt() and b.isInt()){
        bool result = (a.getInt() == b.getInt());
        calcStack.push(Datum(result));
    }
    else if(a.isRString() and b.isRString()){
        bool result = (a.getRString() == b.getRString());
        calcStack.push(Datum(result));
    }
    else{
        calcStack.push(Datum(false));
    }
}

/*
 * name:      RPNCalc parseRString function
 * purpose:   parses an input stream, and returns the rstring representation
 * arguments: an input stream
 * returns:   the string inside the curly brackets
 * effects:   essentially parses a user input that represents an rstring.
 *            Continues reading input until all opening brackets are matched,
 *            and returns the final rstring.
 */
std::string RPNCalc::parseRString(std::istream &input)
{
    string rstring = "";
    int count = 1; // this represents the number of opening brackets
    string thing;
    while(count > 0 and not input.eof()){
        input >> thing;
        if(thing == "}"){
            count--; //if a closing bracket is found, decrement count
        }
        if(thing == "{"){
            count++; //if an opening bracket is found, increment count
        }
        rstring +=  " " + thing;
    }
    if(count != 0){
        //if the input is done and the brackets are not matched, throw error
        throw runtime_error("bad rstring");
    }
    else{
        return "{" + rstring;
    }
}

/*
 * name:      RPNCalc.cpp runExc function
 * purpose:   runs when a user calls the 'exec' command, which executes an
 *            rstring
 * arguments: none
 * returns:   none
 * effects:   pops the datum from the top of the stack, which must be an
 *            rstring, and runs the helper function
 */
void RPNCalc::runExec()
{
    try{
        Datum a = calcStack.top();
        calcStack.pop();
        runRstring(a);
    }
    catch(std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp runRstring function
 * purpose:   reads in an rstring as a stringstream of commands
 * arguments: a datum
 * returns:   none
 * effects:   pushes the string inside the brackets of an rstring into a
 *            stringstream object, and then uses the runHelper function to
 *            run the rstring's commands. The result is then pushed back onto
 *            the calculator's stack.
 */
void RPNCalc::runRstring(Datum a)
{
    stringstream rstring;
    try{
        rstring << removeBrackets(a.getRString());
    }
    catch(const std::runtime_error &e){
        cerr << "Error: cannot execute non rstring\n"; 
    }
    runHelper(rstring);
}

/*
 * name:      RPNCalc.cpp removeBrackets function
 * purpose:   removes the outer brackets of a given rstring
 * arguments: an string with brackets
 * returns:   the string without the outermost brackets
 * effects:   removes the outer brackets of an rstring and returns the inner
 *            text and commands
 */
std::string RPNCalc::removeBrackets(std::string input)
{
    string result = input.substr(2, input.length() - 3);
    return result;
}

/*
 * name:      RPNCalc.cpp runFile function
 * purpose:   runs a file with commands and pushes the result to the stack
 * arguments: none
 * returns:   none
 * effects:   pops an rstring on the top of the calculator's stack, which must
 *            contain a filename. Opens the file and runs the file through
 *            the helper function as an ifstream.
 */
void RPNCalc::runFile()
{
    ifstream input;
    try{
        Datum a = calcStack.top();
        calcStack.pop();
        try{
            string filename;
            filename = removeBrackets(a.getRString());

            //note: removeBrackets keeps the extra space at the end of the
            //      string.
            filename = filename.substr(0, filename.length() - 1);
            input.open(filename);
            if(not input.is_open()){
                cerr << "Unable to read " + filename + "\n";
            }
            else{
                runHelper(input); //if no errors, run the file
            }
        }
        catch(const std::runtime_error &e){
            cerr << "Error: file operand not rstring\n"; 
        }
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
    input.close();
}

/*
 * name:      RPNCalc.cpp runIf function
 * purpose:   runs the 'if' command if prompted by the user
 * arguments: none
 * returns:   none
 * effects:   pops three datums off the stack. The first datum popped should
 *            be an rstring that is run if the condition is false. The second
 *            datum is run if the condition is true. The last datum is the
 *            boolean condition that will be tested.
 */
void RPNCalc::runIf()
{
    try{
        Datum falseCase = calcStack.top(); //falseCase
        calcStack.pop();
        Datum trueCase = calcStack.top(); //trueCase
        calcStack.pop();
        Datum testCondition = calcStack.top(); //bool condition
        calcStack.pop();
        runIfHelper(trueCase, falseCase, testCondition);
    }
    catch(const std::runtime_error &e){
        cerr << "Error: " << e.what() << endl;
    }
}

/*
 * name:      RPNCalc.cpp runIfHelper function
 * purpose:   helper command that runs the if command
 * arguments: three Datums
 * returns:   none
 * effects:   The first datum popped should be an rstring that is run if the 
 *            condition is false. The second datum is run if the condition is
 *            true. The last datum is the boolean condition that will be
 *            tested.
 */
void RPNCalc::runIfHelper(Datum trueCase, Datum falseCase,
                          Datum testCondition)
{
    try{
        if(testCondition.getBool()){
            try{
                trueCase.getRString();
                falseCase.getRString();
                runRstring(trueCase);//calls helper function to run rstring
            }
            catch(const std:: runtime_error &e){
                cerr << "Error: expected rstring in if branch\n";
            }
        }
        else{
            try{
                trueCase.getRString();
                falseCase.getRString();
                runRstring(falseCase);
            }
            catch(const std:: runtime_error &e){
            cerr << "Error: expected rstring in if branch\n";
            }
        }
    }
    catch(const std::runtime_error &e){
        cerr << "Error: expected boolean in if test\n";
    }
}