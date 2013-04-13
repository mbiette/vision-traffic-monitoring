#include "stdafx.h"
#include "Video.h"

Video::Video(const char* path)
{	
	this->stream = cvCreateFileCapture(path);
	if(this->stream)this->next();
	else exit(EXIT_FAILURE);
}

Video::~Video()
{	
	cvReleaseCapture(&stream);
}

void Video::next(int frameDrop)
{
#ifdef DEBUG_CALLS
	std::cout << "Video next called.\n";
#endif
	IplImage* img;
	do
	{
		cvGrabFrame(stream);
		frameDrop--;
	}while(frameDrop>=0);
	img = cvRetrieveFrame(stream);
	if(img) this->actualImage = img;

}

Frame* Video::getFrame()
{
#ifdef DEBUG_CALLS
	std::cout << "Video getFrame called.\n";
#endif
	Frame* frame = NULL;
	if(this->actualImage) frame = new Frame(cvCloneImage(this->actualImage));
	return frame;
}
