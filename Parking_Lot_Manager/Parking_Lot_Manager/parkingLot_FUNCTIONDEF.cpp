#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>

#include "parkingLot_CLASSDEF.h"


void parkingLot::setup(int levels, int rows, int columns, spotType sType) {
	levelSet.resize(levels, lotLevel(rows, columns, sType));
}

void parkingLot::addLevel(int whereTo, int howMany, int rows, int columns, spotType s )
{
	for (int i = 0; i < howMany; i++) {
		lotLevel tempLevel(rows, columns, s);
		levelSet.insert((levelSet.begin()+(whereTo-1+i)),tempLevel);
	}
}

void parkingLot::addRow(int whereTo, int howMany, int whichLevel, spotType s)
{
	if (whichLevel == -999) {
		for (int i = 0; i < levelSet.size(); i++) {
			if (whereTo == -999)
				levelSet[i].addRow(levelSet[i].getRowCount(), howMany, s);
			else
				levelSet[i].addRow(whereTo, howMany, s);

		}
		
	}
	else
	{
		levelSet[whichLevel - 1].addRow(whereTo, howMany, s);
	}
}

void parkingLot::addCol(int whereTo, int howMany, int whichLevel, spotType s)
{
	if (whichLevel == -999) {
		for (int i = 0; i < levelSet.size(); i++) {
			if (whereTo == -999)
				levelSet[i].addCol(levelSet[i].getColCount(), howMany, s);
			else
				levelSet[i].addCol(whereTo, howMany, s);

		}

	}
	else
	{
		levelSet[whichLevel - 1].addCol(whereTo, howMany, s);
	}
}

void parkingLot::deleteLevel(int position, unsigned int howMany)
{
	levelSet.erase(levelSet.begin()+position-1, levelSet.begin()+position-1 + howMany);


}

void parkingLot::resize(int size)
{
	levelSet.clear();
	levelSet.resize(size);
}

lotLevel& parkingLot::operator[](unsigned int i) {
	if (i > levelSet.size())
		throw genExcept("The lot does not have this many levels. Please edit the lot, or enter a valid level number.");

	return levelSet[i];

}

int parkingLot::getAmountOfType(int spotType) {

	int total = 0;

	if (levelSet.empty())
		return total;
	else
		for (int i = 0; i < levelSet.size(); i++) {
			total += levelSet[i].getAmountOfType(spotType);
		}

	return total;
}


int parkingLot::Search(int spotType) {
	if (levelSet.empty())
		throw genExcept("Cannot Perform This operation on a non-existant level");

	int numOfFreeSpaces = 0;
	for (int i = 0; i < levelSet.size(); i++) {

		numOfFreeSpaces += levelSet[i].getAmountFree(spotType);

	}
	return numOfFreeSpaces;
}
//bool parkingLot::notSaved() const
//{
//	return ! saved;
//}
void parkingLot::reserve(int level, int row, int column, spotType spotType) {
	levelSet[level].reserve(row, column, spotType);
}

void parkingLot::view() const
{
	if (levelSet.empty())
		throw genExcept("Cannot perform this operation on an empty parking lot. Please create a parking lot first.");

	std::cout << "\nFull Lot View -------------------\n\n";
	for (int i = 0; i < levelSet.size(); i++) {
		std::cout << "Level " << i + 1 << " View ----------\n\n";
		levelSet[i].view();
		std::cout << std::endl;
	}
	std::cout << "\nKey : m = motorcycle space\n      c = compact space\n      large = large space\n     (!) An 'X' represents a reserved space (!)\n\n";
}

std::string parkingLot::getLotName() const {
	return parkingLotName;
}

int parkingLot::getLevelCount() const {
	return levelSet.size();
}

int parkingLot::getRowCount() const
{
	if (levelSet.empty())
		genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");

	return levelSet[0].getRowCount();
}

int parkingLot::getColCount() const {

	if (levelSet.empty())
		throw genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");

	return levelSet[0].getColCount();
}

void parkingLot::readFromFile(char filename[]) {

	std::ifstream file;

	file.open(filename, std::fstream::in);

	if (!(file.is_open()))
		throw genExcept("File Did not open");

	std::string testString;
	char testChar;
	//std::ifstream x;

	getline(file, testString, '\n');
	if (testString != "*ParkingLotFormat*{")
		throw genExcept("The File is either non-existant or currupt");
	//std::cin.get(testChar);
	//std::cout << "INLOTFUNC\n";
	levelSet.resize(0);
	parkingLot tempLot(0,0,0,motorcycle);
	lotLevel tempLevel;

	//find how many levels there are in the parking lot file.
	//int levelCount = 0;
	//while (!file.eof()) {
	//	getline(file, testString, '\n');
	//	levelCount++;
	//}

	//file.clear();
	//file.seekg(0);
	//getline(file, testString, '\n');

	int y = 0;
		for (int i = 0; ; i++) {
			y = i;
			if (file.eof())
				break;
			tempLot.levelSet.push_back(tempLevel);
			file >> tempLot.levelSet[i];
			levelSet.push_back(tempLot.levelSet[i]);
			//tempLot.levelSet[i].view();

			
		}
		if (tempLot.levelSet[tempLot.levelSet.size() - 1](0, 0).view() == '?') {
			tempLot.levelSet.resize(tempLot.levelSet.size() - 1);
		}


	parkingLotName = filename - ".txt";

	
	levelSet = tempLot.levelSet;


	throw success("Parking lot successfully loaded from file.");
	

}

void parkingLot::saveToFile(char filename[]) {

	std::fstream file;
	file.open(filename, std::fstream::out); 

	file << "*ParkingLotFormat*{";

	for (int i = 0; i < levelSet.size(); i++) {
		file << '\n';
		file << levelSet[i];
		

	}

	file << "}";

	parkingLotName = filename;

	throw success("Parking lot saved to file " + std::string(filename));

	return;

}

std::ostream& operator << (std::ostream& os, const parkingLot& lot) {
	for (unsigned int i = 0; !os ; i++) {
		//os << lot[i];
		os << '\n';
	}
	return os;
}

parkingLot::parkingLot(int levels, int rows, int columsn, spotType s, std::string lotName, bool isSaved) {
	parkingLotName = lotName;
	saved = isSaved;

	for (int i = 0; i < levels; i++) {
		levelSet.push_back(lotLevel(rows, columsn, s));
	}
}
std::istream& operator >> (std::istream& is, parkingLot& lot) {


	return is;
}

