//UI.DECLARATIONS.h
//This file contains declarations of all Menu/UI related functions

#include "CLASSDEF.h"
#include "exceptions_CLASSDEF.h"
#include "parkingSpace_CLASSDEF.h"
#include "lotLevel_CLASSDEF.h"
#include "parkingLot_CLASSDEF.h"

#ifndef UI_DECLARATIONS
#define UI_DECLARATIONS

void programHeader();											//Just a header for aesthetic purposes

void mainMenu(int selector[], parkingLot&);						//Main menu, offers user to setup, edit/reserve, look for capacity, view, load/save lots and exit

void setupMenu(int selector[], parkingLot&);					//Menu to setup a parking lot.


void fileIoMenu(int selector[], parkingLot&);					//Menu to load or save from a file
	void savePrompt(int selector[], parkingLot& lot);			//Menu to save a parkingLot to a file
	void loadPrompt(int selector[], parkingLot& lot);			//Menu to load a parkingLot from a file

void editMenu(int selector[], parkingLot& lot);					//Menu that asks a user whether they want to reserve a spot or edit the lot

void capacityMenu(int selector[], parkingLot& lot);				//Shows the capacity of the lot - how many spaces total, how many of each type, and how many free of each type
	void outputLotInfo(parkingLot& lot);						//Does the above for the entire lot
	void outputLevelInfo(parkingLot& lot, int level);			//Does the above for a selected lot level.


void viewMenu(int selector[], parkingLot& lot);					//Outputs a set of tables, each of which represents a parking lot level
	void reservePrompt(int selector[], parkingLot& lot);		//Reserves a parking spot, asks the user for the place and vehicle type
	void editPrompt(int selector[], parkingLot& lot);			//Edits the parking lot dimensions and spot types.



void menuManager(int selector[], int level, parkingLot& lot);	//Calls the appropriate menu function


void fixInputStream();											//For fixing the input stream when invalid input is entered
void discardExcessInput();										//For discarding excess input after the input stream is cleared. Used in "fixInputStream()"

#endif // !UI_DECLARATIONS


