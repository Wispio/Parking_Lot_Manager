#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "lotLevel_CLASSDEF.h"
#include "exceptions_CLASSDEF.h"



void lotLevel::assignType(spotType sType) {
	if (lotGrid.empty())
		throw genExcept("The parking lot is empty. This operation cannot be performed on an empty parking lot.");

	for (int i = 0; i < lotGrid.size(); ++i) {
		for (int j = 0; j < lotGrid[i].size(); ++j) {
			(lotGrid[j][i]).setup(sType, false);

		}
	}

}
void lotLevel::assignType(int row, bool isRow, spotType sType) {
	if(isRow)
		for (int i = 0; i < lotGrid[row].size(); i++) {

			lotGrid[row][i].setup(sType, false);

		}
	else
		for (int i = 0; i < lotGrid.size(); i++) {
			lotGrid[i][row].setup(sType, false);
		}
}
void lotLevel::assignType(int row, int col, spotType sType) {

	lotGrid[row][col].setup(sType, false);

}
void lotLevel::userAssignType(int row) {
	if (lotGrid.empty())
		throw genExcept("Cannot Perform This operation on a non-existant level");

	char* userInput = new char[256];

	std::cout << "Please enter in the type of spots you would like to put in the row (m,c,l).\n\n";
	std::cout << "Example input: mclclm\n\n";
	std::cout << "Spot types: ";
	std::cin >> userInput;
	std::cout << "userInput";

	for (int i = 0; i < lotGrid[row].size(); i++) {
		if (userInput[i] != 'c' && userInput[i] != 'C' &&
			userInput[i] != 'm' && userInput[i] != 'm' &&
			userInput[i] != 'l' && userInput[i] != 'L')
			throw genExcept("Invalid Input, please try again");
	}

	for (int i = 0; i < lotGrid[row].size(); i++) {

		spotType temp = unspecified;
		if (userInput[i] == 'c' || userInput[i] == 'C')
			temp = compact;
		else if (userInput[i] == 'm' || userInput[i] =='M')
			temp = motorcycle;
		else
			temp = large;

		lotGrid[row][i].setup(temp, false);
	}
}


void lotLevel::reserve(int row, int col, spotType sType) {

	if (lotGrid[row][col].isTaken())
		throw genExcept("You cannot reserve a parking space that is already occupied.");

	if (sType == motorcycle ) {
		lotGrid[row][col].reserve();
	}
	else if (sType == compact) {
		if (lotGrid[row][col].getType() == compact || lotGrid[row][col].getType() == large)
			lotGrid[row][col].reserve();
		else if (lotGrid[row][col].getType() == motorcycle)
			throw genExcept("You cannot park a car in a motorcycle space. Please choose another spot.");
		else
			throw genExcept("The type of space has not yet been specified and thus cannot be reserved. Please specify its type through the edit menu first.");
	}
	else if (sType == large) {
		if (col + 5 > lotGrid[row].size())
			throw genExcept("You must park the bus further from the right edge of the parkign lot level.");

		bool parkable = true;
		for(int i = 0; i < 5; i++)
			if (lotGrid[row + i][col].getType() != large) {
				parkable = false;
			}

		if (parkable)
			for (int i = 0; i < 5; i++)
				lotGrid[row][col + i].reserve();
		else
			throw genExcept("There are not enough free spaces after the chosen spot to reserve the bus");

	}
	return;
	
}

int lotLevel::getAmountOfType(int spotType) {
	if (lotGrid.empty())
		throw genExcept("This operation cannot be performed on an empty or non-existent parking lot. Please create a lot first.");

	int numOfType = 0;

	for (int i = 0; i < lotGrid.size(); i++) {
		for (int j = 0; j < lotGrid[0].size(); j++) {
			if (spotType == -1)
				numOfType++;
			else if (spotType == lotGrid[i][j].getType())
				numOfType++;
		}
	}
	return numOfType;
}

int lotLevel::getAmountFree(int spotType){
	if (lotGrid.empty())
		throw genExcept("This operation cannot be performed on an empty or non-existant lot. Please create a lot first.");

	int numOfFree = 0;

	for (int i = 0; i < lotGrid.size(); i++) {
		for (int j = 0; j < lotGrid[0].size(); j++) {
			if(spotType == -1)
				numOfFree += int(!lotGrid[i][j].isTaken());
			else {
				if (spotType == lotGrid[i][j].getType())
					numOfFree += int(!lotGrid[i][j].isTaken());
			}

		}
	}

	return numOfFree;

}

void lotLevel::view(int spotType) const {
	if (lotGrid.empty())
		throw genExcept("Can't perform this operation on an empty lot");

	//std::cout << lotGrid[0].size() << " " << lotGrid.size() << std::endl;
	int x = 0;

	for (int i = 0; i < lotGrid.size(); i++) {
		std::cout << "Row " << i+1  << "     ";
		for (int j = 0; j < lotGrid[0].size(); j++) {
			x = j;
			std::cout << std::right << std::setw(5);

			if (spotType == -1)
				std::cout << lotGrid[i][j].view();
			else
				if (int(spotType) == lotGrid[i][j].getType())
					std::cout << lotGrid[i][j].view();
				else
					std::cout << '*';
			

		}
		std::cout << std::endl;
		//std::cout << "x\n";
		//std::cout << i << " " << x << std::endl;
	}
	//std::cout << "GOT HERE\n";
}

//void reserve();
//void reserve(int row, int col, spotType sType);


int lotLevel::getRowCount() const {
	if(lotGrid.empty())
		genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");;

	return lotGrid.size();
}
int lotLevel::getColCount() const {
	if (lotGrid.empty())
		throw genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");

	return lotGrid[0].size();
}

void lotLevel::addRow(int whereTo, int howMany, spotType sType) {
	if (whereTo < 0)
		throw genExcept("Please enter a valid row number (>0).");

	for (int i = 0; i < howMany; i++) {
		std::vector<parkingSpace> tempRow(getColCount(), parkingSpace(sType));
		lotGrid.insert(lotGrid.begin() + whereTo+i, tempRow);
	}
}


void lotLevel::addCol(int whereTo, int howMany, spotType sType) {
	if (whereTo < 0)
		throw genExcept("Please enter a valid column number (>0).");

	for (int i = 0; i < lotGrid.size(); i++) {
		for (int j = 0; j < howMany; j++) {

			lotGrid[i].insert( lotGrid[i].begin() + whereTo+j , parkingSpace(sType));


		}
	}
}

void lotLevel::deleteRow(int position, int howMany) {
	if (position < 0)
		throw genExcept("Please enter a valid row number (>0).");
	if (lotGrid.empty())
		throw genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");;

	for (int i = 0; i < howMany; i++) {
		lotGrid.erase(lotGrid.begin() + position);
		//position++;
	}

}
void lotLevel::deleteCol(int position, int howMany) {
	if (position < 0)
		throw genExcept("Please enter a valid column number (>0).");
	if (lotGrid[0].empty())
		throw genExcept("This operation cannot be completed on an unitialized parking lot. Please setup the lot first.");

	for (int i = 0; i < lotGrid.size(); i++) {
		for (int j = 0; j < howMany; j++) {
			lotGrid[i].erase(lotGrid[i].begin() + position);
			//position++;
		}
	}
}

std::vector<parkingSpace>& lotLevel::operator()(unsigned int i) {
	return lotGrid[i];

}
parkingSpace& lotLevel::operator()(unsigned int i, unsigned int j) {
	return lotGrid[i][j];
}



std::istream& operator >> (std::istream& is, lotLevel& grid) {


	char activeChar = NULL;
	char peekChar = NULL;
	spotType sType;
	bool occupied;

	std::vector < std::vector<parkingSpace> > tempLevel;
	std::vector<parkingSpace> tempRow;

	unsigned int col = 0;
	unsigned int row = 0;

	while ((activeChar != '\n' && peekChar != '\n' )) {
		occupied = true;
		is.get(activeChar);

		if (activeChar == '}') {
			break;
		}

		if (activeChar == '/') {

			tempLevel.push_back(tempRow);
			tempRow.clear();
			tempRow.resize(0);
			//grid.lotGrid = tempLevel;
			//std::cout << "ADDEDROW\n";

			//std::cout << activeChar << std::endl;
		} 
		else {

			if (int(activeChar) > 90) {
				//std::cout << "MEME\n" << std::endl;
				occupied = false;
				activeChar -= 32;

			}

			if (int(activeChar) <=90) {

				switch (int(activeChar)) {
				case 67:
					sType = compact; break;
				case 76:
					sType = large; break;
				case 77: 
					sType = motorcycle; break;
				default:
					//std::cout << activeChar;
					if (is.eof())
						return is;
					throw genExcept("Cannot read file.lol data is corrupted."); break;
				}

			}
				parkingSpace tempspace(sType, occupied);
				//std::cout << "obj: " << tempspace.getType() << std::endl;
				tempRow.push_back(tempspace);
			//std::cout << "pushback\n";
		}

		
		peekChar = is.peek();
		//std::cout << "PEEKCHAR: " << peekChar << std::endl;
		

	}

	//std::cout << "END " << peekChar << activeChar;
	if (peekChar == '\n')
		is.get(peekChar);

	//std::cout << std::endl;
	grid.lotGrid = tempLevel;

	//std::cout <<"View"<< std::endl;
	//grid.view();


	return is;
}

std::ostream& operator <<(std::ostream& os, const lotLevel& grid) {

	for (int i = 0; i < grid.lotGrid.size(); i++) {
		for (int j = 0; j < grid.lotGrid[0].size(); j++) {
			char outputChar = '?' ;

			if (grid.lotGrid[i][j].getType() == motorcycle)
				outputChar = 'M';
			else if (grid.lotGrid[i][j].getType() == compact)
				outputChar = 'C';
			else if (grid.lotGrid[i][j].getType() == large)
				outputChar = 'L';

			if (!grid.lotGrid[i][j].isTaken()) {
				outputChar += 32;
			}
			os << outputChar;
		}
		os << '/';
	}
	//grid.view();

	return os;
}

lotLevel::lotLevel(int rows, int columns, spotType sType) {

	lotGrid.resize(rows, std::vector<parkingSpace>(columns, parkingSpace(sType)));

}