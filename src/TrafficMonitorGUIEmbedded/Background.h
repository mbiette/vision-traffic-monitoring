#ifndef INC_BACKGROUND
#define INC_BACKGROUND
#include "basic.hpp"
#include "opencv.h"
#include "Interface.h"
#include "Frame.h"
#include "Video.h"

class Background: public Interface
{
private:
	Interface *source;
	Frame actualBackground;
	Frame *currentFrame;

	void backgroundExtraction();
	void backgroundSubtractionAndUpdate();

public:
	Background(Interface* source);
	~Background();

	Frame* getFrame();
	void next(int frameDrop=0);
};

#endif