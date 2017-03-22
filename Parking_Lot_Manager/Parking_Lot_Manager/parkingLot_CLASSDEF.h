//FILE: parkingLot_CLASSDEF.h
//Provides the definition of the class "parkingLot", which represents a full parking Lot

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "lotLevel_CLASSDEF.h"
#include "exceptions_CLASSDEF.h"
#include "parkingSpaceEnumType.h"

#ifndef parkingLot_CLASSDEF
#define parkingLot_CLASSDEF

//INHERITANCE EXAMPLE
class parkingLot : public lotLevel {
public:


	void reserve(int, int , int, spotType spotype);												//Reserve 1 parking space

	int Search(int spotType = -1);																//POLYMORPHISM VIA OVERLOADING Returns the amount of Free spaces of a given parking space type. If parameter is -1, it returs the total amount free with no regard for type

	int getAmountOfType(int spotType = -1);														//POLYMORPHISM VIA OVERLOADING Returns the amount of spaces of a given parking space type. If parameter is -1, it returns the total number of spaces in the lot

	//bool notSaved() const;

	void setup(int levels, int rows, int columns, spotType = unspecified);						//Creates a parking space object of a single type, with dimensions as parameters

	void addLevel(int whereTo, int rows, int columns, int howMany = 1, spotType s = compact);	//Adds a level to the lot
	void addRow(int whereTo, int howMany = 1, int whichLevel = -999, spotType = compact);		//Adds a row to a level. If the level specified is -999, adds to all levels
	void addCol(int whereTo, int howMany = 1, int whichLevel = -999, spotType = compact);		//Adds a column to a level. If the level specivied is -999, adds to all levels

	void deleteLevel(int position, unsigned int howMany = 1);									//Function to delete a level
	void resize(int);																			//Function to resize the private vector

	int getLevelCount() const;																	//Returns number of levels
	int getRowCount() const;																	//Returns number of rows
	int getColCount() const;																	//Returns number of columns

	void view() const;																			//Outputs tables for each level of the lot
	std::string getLotName() const;	

	//IO of a parking lot
	void saveToFile(char fileName[]);															//Saves the lot to a file. It will define its own fstream variables
	void readFromFile(char filename[]);															//Reads information from a file into a parkingLot ovject 

	lotLevel& operator[](unsigned int);															//Returns the level(floor). Can be compunded with the overloaded operator (uint_8, uint_8) of the lotlevel class

	//Default constructor.
	parkingLot(int levels = 0, int rows = 0, int columns = 0, spotType s = motorcycle,std::string = "unnamedLot", bool saved = false);

private:
	std::vector<lotLevel> levelSet;																//AGREGATION - a vector of lotLevel objects.
	bool saved = false;
	std::string parkingLotName = "unnamedLot";
};

#endif