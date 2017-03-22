//FILE: lotLevel_CLASSDEF.h
//This file contains the definition of the class "lotLevel", which represents a single lot of the parking lot

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "parkingSpace_CLASSDEF.h"
#include "exceptions_CLASSDEF.h"
#include "parkingSpaceEnumType.h"

#ifndef lotLevel_CLASSDEF
#define lotLevel_CLASSDEF

class lotLevel : public parkingSpace {
public:

	void assignType(spotType);						//Assign the whole level to a particular type
	void assignType(int,bool isRow, spotType);		//Assign a whole row to a particular type
	void assignType(int, int, spotType);			//Assign one specific space to a particular type
	void userAssignType(int row);					//Have the user input the parking space types manually for a row

	void reserve(int, int, spotType);				//Reserves a spot

	
	int getRowCount() const;						//Returns number of rows
	int getColCount() const;						//Returns number of columns

	
	void addRow( int whereTo, int howMany = 1, spotType sType = unspecified);	//Adds a Row at the specified position
	void addCol( int whereTo, int howMany = 1, spotType sType = unspecified);	//Adds a Column at the specified position

	void deleteRow(int position, int howMany = 1);								//Delete a row at the specified position
	void deleteCol(int position, int howMany = 1);								//Delete a row at the specified position

	int getAmountOfType(int spotType = -1);										//Returns the amount of spaces of a certain type for a level. If parameter is -1, returns the total number of spaces regardless of type
	int getAmountFree(int spotType = -1);										//Returns the amount of free spaces of a cretain type for a level. If paramater is -1, returns the total number of spaces free, regardless of type
	void view(int spotType = -1) const;											//Returns the Outputs a table representing a lot level to the console. If parameter is not -1, it only displays the spot type relating to the integer entered

	//Default constructor
	lotLevel(int rows = 1, int columns = 1, spotType = unspecified);

	//Overload (unsigned int) to mimic "[]", and "(unsigned int, unsigned int)" to mimic "[][]"
	std::vector<parkingSpace>& operator()(unsigned int); // polymorphism
	parkingSpace& operator()(unsigned int, unsigned int); //polymorphism

	//For intput/output of a level
	friend std::istream& operator >> (std::istream&, lotLevel&);
	friend std::ostream& operator << (std::ostream&, const lotLevel&);

private:
	std::vector< std::vector<parkingSpace> > lotGrid;							//2d vector to represent a single parking lot level

};

#endif