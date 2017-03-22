#include <iostream>

#include "parkingSpace_CLASSDEF.h"

//MEMBER FUNCTIONS

void parkingSpace::setup(spotType sType, bool occupiedStatus) {
	type = sType;
	taken = occupiedStatus;
}

bool parkingSpace::isTaken() const {
	return taken;
}

bool parkingSpace::isFree() const {
	return !taken;
}

spotType parkingSpace::getType() const {
	return type;
}

void parkingSpace::reserve() {
	if (taken)
		throw genExcept("You cannot reserve a spot that is already taken.");
	else
		taken = true;
}

int parkingSpace::search() const {
	return taken;
}

char parkingSpace::view() const {
		switch (type) {
		case unspecified:
			return '?'; break;
		case motorcycle:
			if (taken) return 'X';
			return 'm'; break;
		case compact:
			if (taken) return 'X';
			return 'c'; break;
		case large: 
			if (taken) return 'X';
			return 'l'; break;
		}

}

void parkingSpace::assignType(spotType sType) {
	if (sType < 0 || sType > 3)
		throw ("This is not a valid type of parking space.");
	else
		type = sType;
}


parkingSpace::parkingSpace(spotType sType, bool occupiedStatus) {
	type = sType;
	taken = occupiedStatus;
}

