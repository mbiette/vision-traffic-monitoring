#include "stdafx.h"
#include "Compare.h"

Compare::Compare()
{
}

string Compare::getName(objectType type) {
	string retour;
	switch(type) {
		case PEDESTRIAN: retour = "Pedestrian"; break;
		case CAR: retour = "Light"; break;
		case BUS: retour = "Heavy"; break;
		default: retour = "Undefined"; break;
	}
	return retour;
}

objectType Compare::object(double area, double AreaRef1, double AreaRef2) {
	objectType type;

	if (area > 0.0 && area <= AreaRef1) type = PEDESTRIAN;
	else if (area > AreaRef1 && area <= AreaRef2) type = CAR;
	else if (area > AreaRef2 && area < 7000.0) type = BUS;
	else if (AreaRef1 == 0.0 || AreaRef2 == 0.0 || area >= 7000.0 || area <= 0.0) type = UNDEFINED;

	return type;
}