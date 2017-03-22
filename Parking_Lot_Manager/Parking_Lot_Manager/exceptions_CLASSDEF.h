#pragma once
//exceptions_CLASSDEF.h
//Contains definitions of the various exception types used in the program
//Excpetions: success, errors (genExcept), and to exit the program.


#include <iostream>

#ifndef exceptions_CLASSDEF
#define exceptions_CLASSDEF

//Used to output when an action was successfully performed
class success {
public:
	std::string what();

	success();
	success(std::string message);
private:
	std::string successMessage = "Success";
};

//Used to output when an operation cannot be performed, or when invalid input is entered
class genExcept{
public:

	std::string what();

	genExcept();
	genExcept(std::string message);
private:
	std::string errorMessage = "Some Error Occured";
};


//Used to break the while loop in the driver program and end the program.
class endProgram{

public:
	std::string what();

	endProgram();

private:
	std::string exitMessage = "Program exited Successfully\n\n";
};

#endif