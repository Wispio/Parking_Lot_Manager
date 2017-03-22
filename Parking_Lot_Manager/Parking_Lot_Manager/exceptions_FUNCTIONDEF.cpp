//exceptions_FUNCTIONDEF.cpp
//Contains definitions for the constructors and functions of the exception classes

#include <iostream>
#include "exceptions_CLASSDEF.h"


std::string success::what() {
	return successMessage;
}
success::success() {
	successMessage = "Success.";
}
success::success(std::string message) {
	successMessage = message;
}


std::string genExcept::what() {
	return errorMessage;
}
genExcept::genExcept() {
	errorMessage = "Some Error Occured.";
}
genExcept::genExcept(std::string message) {
	errorMessage = message;
}


std::string endProgram::what() {
	return exitMessage;
}
endProgram::endProgram() {
	exitMessage = "Program Exited Successfully\n\n";
}