#ifndef INC_BIRDSEYE
#define INC_BIRDSEYE

#include "basic.hpp"
#include "opencv.h"
#include "Frame.h"
#include "Interface.h"
#include <sys\stat.h>
using namespace std;

void callback(int, int, int, int, void*); //Callback for the cvSetMouseCallback function.

class Points {
private:
	int n;
	char* windowName;
	IplImage* image;
public:
	CvPoint2D32f pts[4];

	Points();
	void setPoint(int x,int y);
	void getPointsFromMouse(char *windowName,IplImage *image);
	
};

class BirdsEye : public Interface {
private:
	Frame *actualFrame;
	CvMat *H;
	Interface *source;
	
	bool isHFileAvailable(string pathToH); // Look for the xml file that contain the values of the matrix H.
	void computeHFromMouse(string pathToH); // Generate the matrix H .
	void getHFromFile(string pathToH); // Extract the value of H from the xml file.
	void changePerspective(); // Edit the perspective of the actualFrame 

public:
	BirdsEye(Interface* source, string pathToImg);
	~BirdsEye();
	CvRect* changeRectPerspective(CvRect* rect);
	Frame* getFrame();
	void next(int frameDrop = 0);
};

#endif