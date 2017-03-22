//Driver(main).cpp
//This program executes the code contained in the included files to operate the parking lot program. Exception handling occurs in this file.

//Include libraries for console and file Input/Output and manipulation, string output, and the vector type
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

//Include class declatrations, the enumerated data type declaration, and the declarations of menu functions
#include "CLASSDEF.h"
#include "parkingSpaceEnumType.h"
#include "UI_DECLARATIONS.h"


int main() {
	
	//An array of integers to keep track of what menu should be shown at a given time
	int menuTracker[7] = { 0,0,0,0,0,0,0 };

	//A parking Lot variable that is manipulated by the user. Use test(3, 3, 3, motorcycle) to start out with a 3x3x3 lot of motorcycle spaces
	parkingLot activeLot, test(3, 3, 3, motorcycle);

	//Display the header of the program once
	programHeader();

	//Display menus, and interract with the user
	while (true) {
		try {
			
			menuManager(menuTracker, menuTracker[1], test);				//Function that Manages Menus, and calls functions to perform operations on the parking lot
		}

		catch (success successfulOperation) {									//Prints out a message when a lot operation completes successfully
			std::cout << std::endl << std::endl;

			std::cout << "Success: " << successfulOperation.what();

			std::cout << std::endl << std::endl;
		}

		catch(genExcept exception){												//Print out an error message. Returns to the menu level where the error occurred.

			std::cout << std::endl << std::endl;

			std::cout << "ERROR: " << exception.what();

			std::cout << std::endl << std::endl;

		}

		catch(endProgram endRoutine) {											//Exit the larger loop via the break statement and end the program (execute "return 0)

			std::cout << std::endl << std::endl;

			std::cout << endRoutine.what();

			std::cout << std::endl << std::endl;

			break;
		}
	}

	

	return 0;
}