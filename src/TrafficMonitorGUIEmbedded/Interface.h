#ifndef INC_INTERFACE
#define INC_INTERFACE

#include "opencv.h"
#include "Frame.h"

class Interface
{
public:
	virtual Frame *getFrame() = 0;
	virtual void next(int frameDrop=0) = 0;
};

#endif
