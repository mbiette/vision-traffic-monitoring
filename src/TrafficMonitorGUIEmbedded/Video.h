#ifndef INC_VIDEO
#define INC_VIDEO

#include "opencv.h"
#include "Frame.h"
#include "Interface.h"

class Video: public Interface
{
private :
	//Variables
	IplImage *actualImage;

public :
	//Variables
	CvCapture *stream;
	//Constructor
	Video(const char* path);

	//Destructor
	~Video();

	//Methods
	void next(int frameDrop=0);
	Frame* getFrame();
	
		
};

#endif