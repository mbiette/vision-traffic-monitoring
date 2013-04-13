#ifndef COMPARE_H_INCLUDED
#define COMPARE_H_INCLUDED
#include "opencv.h"
#include "basic.hpp"


enum objectType{
	PEDESTRIAN,
	CAR,
	BUS,
	UNDEFINED
};

class Compare {

public:
	Compare();
	objectType object(double area, double AreaRef1, double AreaRef2);
	string getName(objectType type);
private:
	double ped;
	double car;
	double bus;
};

#endif