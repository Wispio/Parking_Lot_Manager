#pragma once

#ifndef spotType_ENUM
#define spotType_ENUM

//Enum type to store parking space type. A spot can be for a motorcycle, for a compact (a car) or large (for cars and busses). Unspecified type also exits
enum spotType {
	unspecified = 0,
	motorcycle = 1,
	compact = 2,
	large = 3
};

#endif