//UI_FUNCTIONDEF.cpp
//This file contains definitions of functions used to display the Menus/UI
//See UI_DECLARATIONS.h for more concise information on the purpose of the functions defined here

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "UI_DECLARATIONS.h"



#ifndef UI_FUNCTIONDEF
#define UI_FUNCTIONDEF

//Executes Once in main. Just a pretty Header
void programHeader() {
	std::cout
		<< "-----------------------------------\n"
		<< "||  PARKING LOT MANAGER PROGRAM  ||\n"
		<< "-----------------------------------\n"
		<< "|| CSC 2110, Fall 2016 Project   ||\n"
		<< "|| Alexander Nakhleh fv3491      ||\n"
		<< "-----------------------------------\n";

	std::cout << "\n\n";
}


/*MENU OUTPUT FUNCTIONS*/
//This is the highest menu level. From here, the user can reach all other options.
void mainMenu(int selector[], parkingLot&) {
	int userInput;
		std::cout <<
			"***************************************************************************************************\n"
			"Please select an option by entering the Number corresponding with a menu Selection, and press Enter\n"
			"     1. Set up the Parking Lot\n"
			"     2. Load/Save a Parking Lot\n"
			"     3. Edit the a Parking Lot/ Reserve a Parking Space\n"
			"     4. Look For Capacity\n"
			"     5. View Level Information\n"
			"     6. Exit\n"
			"\n"
			"Selection ->  ";

		std::cin >> userInput;

		if (!std::cin) {
			fixInputStream();
			throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
		}

		//If the input is valid, update the variable used to keep track of the menus (menuManager()). It will call the appropriate menu function.
		//If the input is invalid, throw an exception, and return to this menu;
		if (userInput == 1) {
			selector[0] = userInput;
		}
		else if (userInput == 2) {
			selector[0] = userInput;
		}
		else if (userInput == 3) {
			selector[0] = userInput;
		}
		else if (userInput == 4) {
			selector[0] = userInput;
		}
		else if (userInput == 5) {
			selector[0] = userInput;
		}
		else if (userInput == 6) {
			selector[0] = userInput;
		}
		else
			throw genExcept("Please enter a valid choice.");

}

//Menu that allows a user to set up the parking lot dimensions and space types
void setupMenu(int selector[], parkingLot& Lot) {
	int userInput;
	std::cout <<
		"*********************************************************************************************************\n"
		"Setup Menu. Determine how you would like to set up a Parking Log. Input \"-1\" to return to the Main menu\n"
		"     1. Provide dimensions for the entire Lot\n"
		"     2. Provide dimensions for each lot level individually\n"
		"     3. Provide parking spot Types for the entire Lot (requires that a lot be already created)\n"
		"     4. Provide spot Types for each lot level individually (requires that a lot be already created)\n"
		"\n\nNOTE. If YOU WOULD LIKE TO MANUALLY INPUT SPOT TYPES, REFER TO THE EDIT MENU AFTER CREATING A LOT.\n\n"
		"    -1. Return to the main menu\n"
		"\n"
		"Selection ->  ";
	std::cin >> userInput;
	selector[0] = 1;
	//selector[1] = 2;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	//If user wants to select dimensions for the whole lot, then get input from the user, and create the parking lot.
	if (userInput == 1) {
		selector[1] = 1;
		selector[2] = 2;

		int levels, rows, columns, type;
		std::cout << "\n Please enter the number of levels, rows, and columns, and a type of parking space spot for the entire lot.\n This will overwrite any existing active parking lot.";
		std::cout << "\nLevels: ";
		std::cin >> levels;
		std::cout << "\nRows: ";
		std::cin >> rows;
		std::cout << "\nColumns: ";
		std::cin >> columns;
		std::cout << "\n Parking Spot type (1 = motorcycle, 2 = compact, 3 = large): ";
		std::cin >> type;

		//Throw an exception if there is invalid input
		if (levels < 0 || rows < 0 || columns < 0 || type < 1 || type >3 || !std::cin) {
			fixInputStream();
			selector[1] = 0;
			throw genExcept("Invalid input detected, please try again.");
		}

		//Otherwise, create the parking lot, and output a success message
		selector[1] = 0;
		Lot = parkingLot(levels, rows, columns, spotType(type));
		throw success("Parking Lot successfully Created.");

		return;
	}

	//If the user wants to create the parking lot level by level, the ask for the rows and oolumn dimensions for each lot level
	else if (userInput == 2) {
		selector[1] = 1;
		selector[2] = 3;

		int counter = 0, rows=1, columns=1, type=0;
		std::vector<lotLevel> tempLot;


		//Take user input for a level
		std::cout << "\nPlease enter information (dimensions and parking space type) for each individual level, starting at the first level.\n"
			<< "ENTER ANY NEGATIVE NUMBER OR 0 AS A ROW OR COLUMN DIMENSION, or -1 AS A TYPE TO STOP ADDING LEVELS\n";

		//User can keep adding levels until they input 0 or a negative number as a row or column dimension, or -1 as a type
		while (rows > 0 || columns > 0) {
			std::cout << "\nThere are currently " << counter << " levels.";
			std::cout << "\nRows: ";
			std::cin >> rows;
			std::cout << "\nColumns: ";
			std::cin >> columns;
			std::cout << "\nParking space type (1 = motorcycle, 2 = compact, 3 = large): ";
			std::cin >> type;

			//Check for valid input, then check the input to see if the user wants to stop adding levels
			if (!std::cin || ((type < 1 || type > 3)&& type != -1)) {
				selector[1] = 0;
				throw genExcept("Invalid input detected, please try again.");
			}
			else if (rows < 0 || columns < 0 || type == -1)
				break;
			else {
				counter++;
				tempLot.push_back(lotLevel(rows, columns, spotType(type)));
			}
		}

		//Resize any existing parking lot to the size of the once created, and copy the newly created lot into the existing one
		Lot.resize(tempLot.size());
		for (int i = 0; i < tempLot.size(); i++) {
			Lot[i] = tempLot[i];
		}

		//After creating the lot, return to the main menu
		selector[1] = 0;

		//Output a success message
		throw success("Lot successfully Created.");

		return;
	}

	//If the user wants to edit the spot types of an entire Lot
	else if (userInput == 3) {
		//If there is no exisint parking lot, throw an exception
		if (Lot.getLevelCount() <= 0) {
			selector[1] = 0;
			throw genExcept("This operation cannot be performed on an empty lot. Please create one before performing this operation.");
		}

		int type;

		//Get the desired type from the user
		std::cout << "\nPlease select the type of spot you wish to convert the entire lot to: ";
		std::cout << "\nParking Spot type (1 = motorcycle, 2 = compact, 3 = large): ";
		std::cin >> type;

		//If input is invalid, throw an exception and return to the main menu. If it is valid, change the spot type of the lot to the desired type.
		if (type < 1 || type > 3 || !std::cin) {
			fixInputStream();
			selector[1] = 0;
			throw genExcept("Invalid input detected, please try again.");
		}
		else
			for(int i = 0; i < Lot.getLevelCount(); i++)
				Lot[i].assignType(spotType(type));


		//Return to main menu and output a success message
		selector[2] = 3;
		selector[1] = 0;
		throw success("Level operation successfully completed.");

	}

	//If the user wants to change the parking space types level by level
	else if (userInput == 4) {

		int type;

		//THrow exception if there is not lot to operate on
		if (Lot.getLevelCount() <= 0) {
			selector[1] = 0;
			throw genExcept("This operation cannot be performed on an empty lot. Please create one before performing this operation.");
		}


		// get a spot type for each level of the lot. Check the input. If it is valid, reassign the level
		for (int i = 0; i < Lot.getLevelCount(); i++) {
			std::cout << "Please input the parking spot type to convert level " << i + 1 << " to :";
			std::cout << "\nParking Spot Type (1 = motorcycle, 2 = compact, 3 = large): ";
			std::cin >> type;

			if (type < 1 || type > 3 || !std::cin) {
				fixInputStream();
				selector[1] = 0;
				throw genExcept("Invalid input detected, please try again.");
			}
			else
				Lot[i].assignType(spotType(type));
		}

		//return to the main menu, output success message
		selector[1] = 0;

		throw success("Level operation successfully completed.");
	}

	//Return to the main menu
	else if (userInput == -1) {
		selector[0] = 0;
		selector[1] = 0;
	}
	else
		throw genExcept("Please enter a valid choice.");
}





//Asks the user for the file to load a parking lot fron
void loadPrompt(int selector[], parkingLot& lot) {
	char* userInput = new char[256];
	std::cout <<
		"Please enter the name of the file to read from (in the form \"fileName.txt\")\n\n"
		"FILE: ";

	std::cin >> userInput;
	std::cout << "INPUTENTERED" << std::endl;

	lot.readFromFile(userInput);

}

//Asks the user what name the current parking lot should be saved under.
void savePrompt(int selector[], parkingLot& lot) {
	char* userInput = new char[256];
	std::cout <<
		"Please enter the name of the file to save to (in the form \"fileName.txt\")\n\n"
		"FILE:";

	std::cin >> userInput;

	lot.saveToFile(userInput);
}

//Asks the user whether they want to load from a file, or save to a file
void fileIoMenu(int selector[], parkingLot& lot) {
	int userInput;


	//Ask the user whether they are saving or loading from a file, take their input, see that it is valid, and then perform the action.
	std::cout <<
		"**************************************************************************************************************\n"
		"Choose to load a saved parking lot from a file, or create a save File. Input \"-1\" to return to the Main menu\n"
		"     1. Load Parking Lot from file\n"
		"     2. Save current Parking Lot to a file\n"
		"    -1. Return to the main menu\n"
		"\n"
		"Selection ->  ";

	std::cin >> userInput;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	if (userInput == 1)
		loadPrompt(selector, lot);
	else if (userInput == 2)
		savePrompt(selector, lot);
	else if (userInput == -1) {
		selector[0] = 0;
	}
	else
		throw genExcept("Please enter a valid choice.");
}



void levelAddMenu(parkingLot& lot) {
	int levelCount, place, rows, columns, s;
	std::cout << "\nPlease enter the amount of levels (and their dimensions and space type) to add, and which existing level to insert them after.\n";
	std::cout << "Amount: ";
	std::cin >> levelCount;
	std::cout << "\nPlace: ";
	std::cin >> place;
	std::cout << "\nRows: ";
	std::cin >> rows;
	std::cout << "\nColumns: ";
	std::cin >> columns;
	std::cout << "\nParking Space Type (1 = motorcycle, 2 = compact), 3 = large): ";
	std::cin >> s;
	if (rows < 0 || columns < 0 || s < 1 || s > 3)
		throw genExcept("Invalid input was detected. Please try editing the lot again");
	lot.addLevel(place + 1, levelCount, rows, columns, spotType(s));

	throw success("Level Operation completed Successfully.");

}
void rowAddMenu(parkingLot& lot) {
	int rowCount, place, whereTo, s, level;
	std::cout << "Please enter the amount of rows to add, which level to add them, and which existing row to insert them after.\n";
	std::cout << "Amount: ";
	std::cin >> rowCount;
	std::cout << "Level: (enter -999 to add to all levels): ";
	std::cin >> level;
	if (level != -999 && level > 1)
		std::cout << "There are currently " << lot[level - 1].getRowCount() << " rows on this level.\n";
	std::cout << "\nPlace (enter -999 to add it to the end of the level: ";
	std::cin >> place;
	std::cout << "\nParking Space Type (1 = motorcycle, 2 = compact), 3 = large): ";
	std::cin >> s;
	std::cout << "\n Which level To add rows to (enter -999 to add rows to all levels): ";

	if ((place < 0 && place != -999) || rowCount < 0 || (level < 0 && level != -999) || s < 1 || s > 3 || !std::cin) {
		fixInputStream();
		throw genExcept("Invalid input was detected. Please try editing the lot again");
	}

	lot.addRow(place, rowCount, level, spotType(s));

	throw success("Level Operation completed Successfully.");

}
void columnAddMenu(parkingLot& lot) {
	int colCount, place, whereTo, s, level;
	std::cout << "Please enter the amount of columns to add, which level to add them to, and which existing column to insert them after.\n";
	std::cout << "Currently, there are " << lot.getLevelCount() << " levels.\n";
	std::cout << "Amount: ";
	std::cin >> colCount;
	std::cout << "Level: (enter -999 to add to all levels): ";
	std::cin >> level;
	if (level != -999 && level > 1)
		std::cout << "There are currently " << lot[level - 1].getColCount() << " columns on this level.\n";
	std::cout << "\nPlace (enter -999 to add it to the end of the level: ";
	std::cin >> place;
	std::cout << "\nParking Space Type (1 = motorcycle, 2 = compact), 3 = large): ";
	std::cin >> s;
	std::cout << "\n Which level To add rows to (enter -999 to add rows to all levels): ";

	if ((place < 0 && place != -999) || colCount < 0 || (level < 0 && level != -999) || s < 1 || s > 3 || !std::cin) {
		fixInputStream();
		throw genExcept("Invalid input was detected. Please try editing the lot again");
	}

	lot.addCol(place, colCount, level, spotType(s));

	throw success("Level Operation completed Successfully.");
}

void spotEditMenu(int selector[], parkingLot& lot) {

	int input;
	selector[1] = 2;
	selector[2] = 0;

	std::cout <<
		"Parking Space Type editing ------------\n"
		"1. Assign a type to the whole Lot\n"
		"2. Assign a type to a whole level\n"
		"3. Assign a type to a row or column within a level\n"
		"4. Assign a type to a single Space\n"
		"-1. Return to the previous menu\n"
		"\n"
		"Selection -> ";
	std::cin >> input;

	//If the user wants to assign a type to the whole lot
	if (input == 1) {
		std::cout <<
			"\nPlease specify the parking space type (1 = compact, 2 = compact, 3 = large): ";
		std::cin >> input;

		if (input < 1 || input > 3)
			throw genExcept("Invalid input was detected. Please try editing the lot again");
		else
			for (int i = 0; i < lot.getLevelCount(); i++) {
				lot[i].assignType(spotType(input));
			}
		selector[1] = 1;
		selector[2] = 1;
	}

	//If the user wants to assign a type to a level
	else if (input == 2) {
		int level, spaceType;
		std::cout << "\nPlease specify the level to modify (there are currently " << lot.getLevelCount() << " levels): ";
		std::cin >> level;
		std::cout <<
			"\nPlease specify the parking space type (1 = compact, 2 = compact, 3 = large): ";
		std::cin >> spaceType ;

		if ((spaceType < 1 || spaceType > 3) || (level < 1 || level > lot.getLevelCount()))
			throw genExcept("Invalid input was detected. Please try editing the lot again");
		else
			lot[level - 1].assignType(spotType(spaceType));


		selector[1] = 1;
		selector[2] = 1;
	}

	//If the user wantes to assign a type to a row or column within a level
	else if (input == 3) {
		int level, rCSelect, position;
		std::cout << "\nPlease specify the level to modify (there are currently " << lot.getLevelCount() << " levels): ";
		std::cin >> level;
		std::cout << "\nPlease specify whether you want to modify a row or column (1 for row, 2 for column): ";
		std::cin >> rCSelect;
		std::cout << "\nPlease select which row or column to edit (currently " << lot[level - 1].getRowCount() << " rows and " << lot[level - 1].getColCount() << "columns): ";
		std::cin >> position;

		if ((rCSelect != 1 && rCSelect != 2))
			throw genExcept("Invalid input was detected. Please try editing the lot again");

		int dimension = (rCSelect == 1 ? lot[level - 1].getRowCount() : lot[level - 1].getColCount());

		if ((level < 1 || level > lot.getLevelCount()) || (rCSelect != 1 && rCSelect != 2) || position > dimension)
			throw genExcept("Invalid input was detected. Please try editing the lot again");

		if (rCSelect == 1) {
			if (position <1 || position > lot[level - 1].getRowCount())
				throw genExcept("Invalid input was detected. Please try editing the lot again");
			else {
				int manualInput;
				std::cout << "Would you like to manually enter values for this row, or would you like to assign all of them to a type?";
				std::cout << "\n(1 = manually, 2 = bulk assignment of a type): ";
				std::cin >> manualInput;


				if ((manualInput != 1 && manualInput != 2) || !std::cin)
					throw genExcept("Invalid input was detected. Please try editing the lot again");


				if (manualInput == 1) {
					std::cout << "\n\n";
					selector[1] = 0;
					lot[level - 1].userAssignType(position - 1);
				}
				else if (manualInput == 2) {

					std::cout <<
						"\nPlease specify the parking space type (1 = motorcycle, 2 = compact, 3 = large): ";
					std::cin >> input;

					if ((input < 1 || input > 3))
						throw genExcept("Invalid input was detected. Please try editing the lot again");

					selector[1] = 0;
					lot[level - 1].assignType(position - 1, true, spotType(input));

				}
			}
			if (rCSelect == 2) {
				if (position <1 || position > lot[level - 1].getColCount())
					throw genExcept("Invalid input was detected. Please try editing the lot again");
				else
					lot[level - 1].assignType(position - 1, false, spotType(input));
			}
		}
		selector[1] = 1;
		selector[2] = 1;
	}

	//If the user wants to assign a type to a single space
	else if (input == 4) {
		int row, col, level;
		std::cout << "\nPlease enter the level number, row number, and column number, of the space you wish to edit\n";
		std::cout << "There are currently " << lot.getLevelCount() << " levels.\n";
		std::cin >> level;

		if (level < 1 || level > lot.getLevelCount())

			throw genExcept("Invalid input was detected. Please try editing the lot again");

		std::cout << "There are currently " << lot[level - 1].getRowCount() << " rows and " << lot[level - 1].getColCount() << " columns on this level.\n";
		std::cout << "Rows: ";
		std::cin >> row;
		std::cout << "Columns: ";
		std::cin >> col;

		if (row < 1 || row > lot[level - 1].getRowCount() || col < 1 || col > lot[level - 1].getColCount())
			throw genExcept("Invalid input was detected. Please try editing the lot again");

		std::cout << "\n Please enter the spot type to convert to (It is currently of type " << lot[level - 1](row - 1, col - 1).view() << ")\n";
		std::cout << "Parking Spot Type (1 = motorcycle, 2 = compact, 3 = large): ";
		std::cin >> input;

		if (input < 1 || input > 3)
			throw genExcept("Invalid input was detected. Please try editing the lot again");

		//If all input is valid, perform the operation
		lot[level - 1].assignType(row - 1, col - 1, spotType(input));
		selector[1] = 0;

		throw success("Level Operation completed Successfully.");
		selector[1] = 1;
		selector[2] = 1;
		return;
	}

	//If user input is -1, return the the edit prompt menu
	else if (input == -1) {
		selector[1] = 1;
		selector[2] = 1;
	}
}

//User prompts to reserve a parking spot
void reservePrompt(int selector[], parkingLot& lot) {
	int spaceType, level, row, column;

	//Ask the user what type of vehicle they are reserving a spot for, and take their input. If it is invalid, throw an exception, and return to this menu
	std::cout <<
		"\nWhat type of vehicle would you like to reserve a spot for? -----\n"
		"    1. Motorcycle\n"
		"    2. Car\n"
		"    3. Bus\n"
		"   -1. Return to the previous menu\n"
		"\n"
		"Selection ->  ";

	std::cin >> spaceType;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	if (spaceType == -1) {
		selector[1] = 0;
		return;
	}
	else if (spaceType != 1 && spaceType !=2 && spaceType != 3)
		throw genExcept("Please enter a valid choice.");


	//Ask user what level they want to park on
	std::cout << "What level would you like to park on? -----\n"
		"Level: ";
	std::cin >> level;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}
	if (level > lot.getLevelCount() || level < 0) {
		throw genExcept("Please enter a valid level number.");
	}


	//Show the user the level they chose, then ask for the row and column of the parking spot they want
	std::cout << "\nLevel " << level << " View -------------------\n\n";
	lot[level-1].view();
	std::cout << "\nKey : m = motorcycle space\n      c = compact space\n      large = large space\n     (!) Uppercase letters represent a reserved space (!)\n\n";

	std::cout << "Choose the row and column of the spot you would like to reserve -----\n"
		"Row : ";
	std::cin >> row;
	std::cout << "\nColumn: ";
	std::cin >> column;


	//Check for invalid inputs
	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}
	if (row > lot.getRowCount() || row < 0) {
		throw genExcept("Please enter a valid column number.");
	}
	if (column > lot.getColCount() || column < 0) {
		throw genExcept("Please enter a valid column number.");
	}

	//If the input is invalid, try reserving the parking space. Throws an exception if the chosen vehicle cannot park in that space
	lot.reserve(level-1, row-1, column-1, spotType(spaceType));

	//Return to the main menu, and print out a successs message
	selector[1] = 0;
	throw (success("Parking Space Reserved;"));

	
}
void editPrompt(int selector[], parkingLot& lot) {
	int userInput;

	//Ask the user what they want to do, 
	std::cout << "\nEdit. Choose an operation -----\n"
		"     1. Add levels\n"
		"     2. Add rows\n"
		"     3. Add columns\n"
		"     4. Delete levels, rows ,or columns\n"
		"     5. Edit Spot Types\n"
		"    -1. Return to the previous menu\n"
		"\n"
		"Selection ->  ";
	std::cin >> userInput;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}
	
	//If input is -1, return to the main menu
	if (userInput == -1) {
		selector[1] = 0;
		selector[0] = 3;
		return;
	}

	//If the user wants to add levels to the parking lot.
	else if (userInput == 1) {
		levelAddMenu(lot);
	}
	//If the user wants to add rows to the parking lot
	else if (userInput == 2) {
		rowAddMenu(lot);
	}

	//If the user wants to add Columns to the parking lot
	else if (userInput == 3) {
		columnAddMenu(lot);
	}

	//If the user wants to delete levels, columns, or rows
	else if (userInput == 4) {
		int input;
		std::cout << "What would you like to delete?-----\n"
			<< "     1. Levels\n"
			<< "     2. Rows\n"
			<< "     3. Columns\n"
			<< "    -1. Return to the previous menu"
			<< "\n"
			<< "selection ->  ";

		std::cin >> input;

		if (!std::cin || input < 1 || input >3) {
			fixInputStream();
			throw genExcept("Invalid input detected, please try again.");
		}

		if (input == 1) {
			int level, amount;

			std::cout
				<< "There are currently " << lot.getLevelCount() << " free levels. "
				<< "Which level would you like to delete?\n\n"
				<< "Level: ";
			std::cin >> level;
			std::cout << "* There are currently " << lot.getLevelCount() - level << "levels above this level"
				<< "How many levels in total would you like to delete?\n"
				<< "*Any input > 1 deletes additional levels after the first selected level.\nInput 1 to delete only one level\n"
				<< "Total number of levels to delete: ";
				
			std::cin >> amount;

			if (!std::cin || (level < 0 || level > lot.getLevelCount()) || (amount < 0 || amount > lot.getLevelCount() - level + 1)) {
				fixInputStream();
				throw genExcept("Invalid input detected, please try again.");
			}

			lot.deleteLevel(level, amount);

			throw success("Level(s) successfully deleted.");
		}
		else if (input == 2) {
			int level, row, amount;
			std::cout
				<< "There are currently " << lot.getLevelCount() << "free levels: "
				<< "\nWhich level would you like to delete a row from ?\n\n"
				<< "Level: ";
			std::cin >> level;

			std::cout << "\nThere are currently " << lot.getColCount() << " rows on this level"
				<< "\n\nWhich row would you like to delete from the level?\n\n"
				<< "Row: ";
			std::cin >> row;

			if (level < 0 || level > lot.getLevelCount()) {
				fixInputStream();
				throw genExcept("Invalid input detected, please try again.");
			}


			std::cout
				<< "\nThere are currently " << lot.getRowCount() - row << " more rows after this row that are deletable.\n"
				<< "*Note: Any input > 1 deletes addition rows after the previously selected row.\n Input 1 to delete only the previously selected row.\n\n"
				<< "\nHow many rows would you like to delete?\n\n"
				<< "Total amount of rows to delete: ";
			std::cin >> amount;

			if (!std::cin || ((level < 0 && level!=-999) || level > lot.getLevelCount()) || (amount < 0 || amount > lot[level].getRowCount() - row + 1)) {
				fixInputStream();
				throw genExcept("Invalid input detected, please try again.");
			}

			lot[level-1].deleteRow(row-1, amount);

			throw success("Rows successfully Deleted.");

		}
		else if (input == 3) {
			int level, column, amount;
			std::cout
				<< "There are currently " << lot.getLevelCount() << " levels: "
				<< "\nWhich level would you like to delete a column from ?\n\n"
				<< "Level: ";
			std::cin >> level;

			if (level < 0 || level > lot.getLevelCount()) {
				fixInputStream();
				throw genExcept("Invalid input detected, please try again.");
			}


			std::cout << "\n\nThere are currently " << lot.getColCount() << " columns on this level"
					<<"\n\nWhich column would you like to delete from the level?\n\n"
					<< "Column: ";
			std::cin >> column;

			

			std::cout
				<< "* There are currently " << lot.getColCount() - column << " columns after this column"
				<< "\nHow many columns would you like to delete?\n\n"
				<< "*Note: Any input > 1 deletes addition columnss after the previously selected row.\n Input 1 to delete only the previously selected column.\n\n"
				<< "Total amount of columns to delete: ";
			std::cin >> amount;

			if (!std::cin || ((level < 0 && level != -999) || level > lot.getLevelCount()) || (amount < 0 || amount > lot[level].getRowCount() - column + 1)) {
				fixInputStream();
				throw genExcept("Invalid input detected, please try again.");
			}

			lot[level].deleteCol(column-1, amount);

			throw success("Columns successfully Deleted.");

		}
		else
			return;
	}

	//If the user wants to edit spot types
	else if (userInput == 5) {
		//Call the spot type editor through menuManager
		selector[1] = 2;
		selector[2] = 0;
	}
		else if (userInput == -1) {
			//Return to the edit/reserve menu
			selector[2] = 0;
			selector[1] = 0;
			selector[0] = 3;
			return;
		}
		else
			throw genExcept("Please chose a valid choice.");

	}

//Menu that allows one to reserve a spot or edit the lot dimensions
void editMenu(int selector[], parkingLot& lot) {

	if (lot.getLevelCount() == 0) {
		selector[0] = 0;
		throw genExcept("This operation cannot be performed on a non-existant parking lot. Please create one first.");
	}

	int userInput;
	std::cout << 
		"****************************************************************************************************\n"
		"Reservations/ Parking Lot Editing Menu. Input \"-1\" to return to the Main menu\n"
		"     1. Reserve a Parking Space\n"
		"     2. Edit the Parking Lot layout (dimensions), and Parking Space Types\n"
		"    -1. Return to the main menu\n"
		"\n"
		"Selection ->  ";

	std::cin >> userInput;
	
	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	//Calls the reserve menu
	if (userInput == 1) {
		selector[1] = 1;
		selector[0] = 0;
		return;
	}
	
	//Calls the menu to edit dimensions
	else if (userInput == 2) {
		selector[1] = 1;
		selector[2] = 1;
		return;
	}
	//Returns to the main menu
	else if (userInput == -1)
		selector[0] = 0;
	else
		throw genExcept("Please enter a valid choice.");
}


//Outputs capacity information about the whole parking lot
void outputLotInfo(parkingLot& lot) {
	std::cout << "Parking Lot Name: " << lot.getLotName() << "\n\n"
		<< "Dimensions----------\n"
		<< "Levels: " << lot.getLevelCount() << "\n"
		<< "Rows: " << lot.getRowCount() << "\n"
		<< "Columns: " << lot.getColCount() << "\n"
		<< "Total number of parking spaces: " << lot.Search() << "\n"
		<< "Total number of occupied Parking Spaces: " << (lot.getAmountOfType()) 
														- lot.Search(motorcycle)
														- lot.Search(compact)
														- lot.Search(large)
														 << "\n\n"
		<< "Spots and Availability----------\n"
		<< "Motorcycle: " << lot.Search(motorcycle) << " free;" << "(Total: " << lot.getAmountOfType(motorcycle) << ")\n"
		<< "Compact: " << lot.Search(compact) << " free;" << "(Total: " << lot.getAmountOfType(compact) << ")\n"
		<< "Large: " << lot.Search(large) << " free;" << "(Total: " << lot.getAmountOfType(large) << ")\n";
}

//Outputs capacity information about a selected lot level
void outputLevelInfo(parkingLot& lot, int level) {
	std::cout
		<< "Level " << level << " ----------\n"
		<< "Rows: " << lot[level].getRowCount() << "\n"
		<< "Columns: " << lot[level].getColCount() << "\n\n"
		<< "Spots and Availability----------\n"
		<< "Motorcycle: " << lot[level].getAmountFree(motorcycle) << " free;" << "(Total: " << lot[level].getAmountOfType(motorcycle) << ")\n"
		<< "Compact: " << lot[level].getAmountFree(compact) << " free;" << "(Total: " << lot[level].getAmountOfType(compact) << ")\n"
		<< "Large: " << lot[level].getAmountFree(large) << " free;" << "(Total: " << lot[level].getAmountOfType(large) << ")\n";

}

//Capacity menu that lets one get capacity information about the whole parking lot, or one specific level
void capacityMenu(int selector[], parkingLot& lot) {
	int userInput;
	std::cout <<
		"***********************************************************************************************************\n"
		"Capacity Menu. Select an option by entering the Number corresponding with a menu Selection, and press Enter\n\n"
		"     1. Get Information on the Entire Parking lot (Dimensions, SpotCount, SpotTypes, amount of Free spaces\n"
		"     2. Get Information on a specific level of the Parking lot\n"
		"    -1. Return to the main menu\n"
		"\n"
		"Selection ->  ";

	std::cin >> userInput;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	//If the user wants information about the whole lot, output it
	if (userInput == 1)
		outputLotInfo(lot);


	//If the user wants information about a specific lot level, ask for the level, then output the information
	else if (userInput == 2) {

		std::cout << "Please enter the level Number: ";
		std::cin >> userInput;
		if (!std::cin) {
			fixInputStream();
			throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
		}
		if (userInput < 0 || userInput > lot.getLevelCount())
			throw genExcept("This level does not exist. Please enter a valid level number.");

		outputLevelInfo(lot, userInput-1);

	}

	//Return to main menu
	else if (userInput == -1) {
		selector[0] = 0;
	}
	else
		throw genExcept(" Please enter a valid choice.");
}

//Outputs a parking lot as a table
void viewMenu(int selector[], parkingLot& lot) {
	int userInput;
	std::cout
		<< "***************************************************************************************************\n"
		<< "View Menu. Provides a graphical representation of the lot. Input \"-1\" to return to the Main menu.\n"
		<< "     1. View All levels of the Lot\n"
		<< "     2. View a certain level\n"
		<< "    -1. Return to the main menu\n"
		<< "\n"
		<< "Selection ->  ";

	std::cin >> userInput;

	if (!std::cin) {
		fixInputStream();
		throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
	}

	//If the user chooses to see the entire lot, view it
	if (userInput == 1) {
		lot.view();
	}

	//If the user chooses to see a lot level, ask for the level, then view that level
	else if (userInput == 2) {

		std::cout << "Please enter the level Number: ";
		std::cin >> userInput;
		if (!std::cin) {
			fixInputStream();
			throw genExcept("Only integer inputs are allowed. Please enter a valid choice.");
		}
		if (userInput < 0 || userInput > lot.getLevelCount())
			throw genExcept("This level does not exist. Please enter a valid level number.");

		std::cout << "\nLevel " << userInput << " View -------------------\n\n";

		lot[userInput-1].view();

		std::cout << "\nKey : m = motorcycle space\n      c = compact space\n      large = large space\n     (!) an 'X' represents a reserved space (!)\n\n";
	}
	//Return to the main menu
	else if (userInput == -1) {
		selector[0] = 0;
	}
	else
		//If the input is not one of the choices, throw an exception
		throw genExcept("Please enter a valid choice.");
}

/*END MENU OUTPUT FUNCTIONS*/



//Function that calls the appropriate menu function based on the contents of the menu-tracking interger array
void menuManager(int selector[] ,int level, parkingLot& lot) {

	//Reset the input stream eavery time the user transitions to a different menu. Done for safety
	//fixInputStream();

	//For selection from the main menu
	if (level == 0) {
		switch (selector[0]) {
		case 0:
			mainMenu(selector, lot); break;
		case 1:
			setupMenu(selector, lot); break;
		case 2:
			fileIoMenu(selector, lot); break;
		case 3:
			editMenu(selector, lot); break;
		case 4:
			capacityMenu(selector, lot); break;
		case 5:
			viewMenu(selector, lot); break;
		case 6:
			throw endProgram(); break; //exit the Program


		}
	}
	//For selection from the Edit Menu
	if (level == 1) {
		switch (selector[2]) {
			case 0:
				reservePrompt(selector, lot); break;
			case 1:
				editPrompt(selector, lot); break;
				//case 2:
					//reservePrompt(selector, lot); break;
			}
		}
	//For selection from the editParking Space subsection of the edit menu
	if (level == 2) {
		switch (selector[2]) {
		case 0:
			spotEditMenu(selector, lot); break;
		}
	}//
	}



//Istream Fixes
void fixInputStream() {
	std::cin.clear();
	discardExcessInput();
}

void discardExcessInput() {
	std::string discard;
	std::getline(std::cin, discard);
}



#endif