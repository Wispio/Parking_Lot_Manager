//FILE: parkingSpace_CLASSDEF.h
//Defines the class "parkingSpace", which represents a single parking space;

#pragma once
#include <iostream>

#include "exceptions_CLASSDEF.h"
#include "parkingSpaceEnumType.h"

#ifndef parkingSpace_CLASSDEF
#define parkingSpace_CLASSDEF

class parkingSpace {
public:

	

	void setup(spotType, bool);					//Function to set up a parking spot
	void assignType(spotType);					//Function to change the type of the 
	void reserve();								//Reserve a parking spot by making the "taken" boolean true
	virtual int search() const;					//Returns the amount of free spaces in a given container of spaces (1 space or a level)
	char view() const;							//Prints the spot to the console as a character
	bool isFree() const;						//Checks whether a spot is free.

	spotType getType() const;					//Returns the enumerat type of spot, as an integer
	bool isTaken() const;						//Returns a boolean depending on whether the given space is occupied or not.

	//Default Constructor
	parkingSpace(spotType sType = motorcycle, bool = false);	//If the type of parking space is not specified, it will be a motorcycle space by default.

private:
	spotType type = unspecified;				//Variable to store the type of spot
	bool taken = false;							//Boolean to store whether the spot is taken or not

};

#endif