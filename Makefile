###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Daniel Peng

MAKEFLAGS += -L 
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds the CalcYouLater executable
CalcYouLater: Datum.o DatumStack.o RPNCalc.o main.o
	$(CXX) $(CXXFLAGS) -o CalcYouLater $^

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

# This rule builds parser.o
# parser.o: parser.cpp
# 	$(CXX) $(CXXFLAGS) -c $^

# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

# This rule builds main.o
main.o: main.cpp RPNCalc.cpp RPNCalc.h DatumStack.cpp DatumStack.h Datum.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule build unit_test
unit_test: unit_test_driver.o DatumStack.o Datum.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^

#
# Provide rule for phase 2!
#
provide:
	provide comp15 proj2_calcyoulater Datum.h DatumStack.h DatumStack.cpp \
			RPNCalc.h RPNCalc.cpp main.cpp \
			testfile1.cylc testfile2.cylc testfile3.cylc \
			parseRStringExample1.txt parseRStringExample2.txt \
			parseRStringFail.txt parseRStringSimple.txt \
			calculate.cylc \
			unit_tests.h Makefile README

# removes executables, object code
clean:
	rm parser.o DatumStack.o main.o RPNCalc.o *~ a.out