#include "stdafx.h"
#include "BirdsEye.h"
using namespace std;

Points::Points()
{
	this->n = 0;
}

void Points::getPointsFromMouse(char *windowName, IplImage *image)
{
	this->windowName = windowName;
	this->image = image;
	cvShowImage( windowName , image );
	cvSetMouseCallback(windowName,callback,this);
	while(n<4) cvWaitKey(1000);
	cvSetMouseCallback(windowName,NULL,NULL);
}
void Points::setPoint(int x, int y)
{
	if(n<4){
		pts[n].x = (double)x;
		pts[n].y = (double)y;
		std::cout << "Coord x : " << pts[n].x << ", Coord y : " << pts[n].y << "\n";
		switch(n)
		{
			case 0: cvCircle( image, cvPointFrom32f(pts[n]), 5, CV_RGB(0,0,255), 2); break;
			case 1: cvCircle( image, cvPointFrom32f(pts[n]), 5, CV_RGB(0,255,0), 2); break;
			case 2: cvCircle( image, cvPointFrom32f(pts[n]), 5, CV_RGB(255,0,0), 2); break;
			case 3:	cvCircle( image, cvPointFrom32f(pts[n]), 5, CV_RGB(255,255,0), 2); break;
		}
		cvShowImage( windowName, image );
		n++;
	}
}
void callback(int event, int x, int y, int flags, void* param) {
	if(event == CV_EVENT_LBUTTONDOWN)
		((Points*)param)->setPoint(x,y);
}

BirdsEye::BirdsEye(Interface *source, string pathToImg)
{
	this->source = source;
	source->next();
	actualFrame = source->getFrame();

	this->H = cvCreateMat( 3, 3, CV_32F);
	pathToImg.append(".xml");
	if(isHFileAvailable(pathToImg)) getHFromFile(pathToImg);
	else computeHFromMouse(pathToImg);

	this->changePerspective();
}

BirdsEye::~BirdsEye()
{
	cvReleaseMat(&H);
	delete this->actualFrame;
	this->actualFrame = NULL;
}

bool BirdsEye::isHFileAvailable(string pathToH)
{
	struct stat stFileInfo; 
	bool blnReturn; 
	int intStat;

	intStat = stat(pathToH.c_str(),&stFileInfo);
	if(intStat == 0) 
	{ 
		// We were able to get the file attributes 
		// so the file obviously exists. 
		blnReturn = true; 
	} 
	else
	{ 
		/*We were not able to get the file attributes. 
		This may mean that we don't have permission to 
		access the folder which contains this file. If you 
		need to do that level of checking, lookup the 
		return values of stat which will give you 
		more details on why stat failed.*/ 
		blnReturn = false;
	}

	return blnReturn;
}

void BirdsEye::computeHFromMouse(string pathToH)
{
	static const int SIZE=50;
	Points *pts = new Points();

	IplImage *temp = cvCloneImage(actualFrame->image);
	pts->getPointsFromMouse("Acquire Perspective",temp);
	cvDestroyWindow("Acquire Perspective");
	cvReleaseImage(&temp);
	
	CvPoint2D32f objPts[4];
	objPts[0].x = (actualFrame->image->width/2)-SIZE; objPts[0].y = (actualFrame->image->height/2)-SIZE;
	objPts[1].x = (actualFrame->image->width/2)+SIZE; objPts[1].y = (actualFrame->image->height/2)-SIZE;
	objPts[2].x = (actualFrame->image->width/2)-SIZE; objPts[2].y = (actualFrame->image->height/2)+SIZE;
	objPts[3].x = (actualFrame->image->width/2)+SIZE; objPts[3].y = (actualFrame->image->height/2)+SIZE;

	cvGetPerspectiveTransform( objPts, pts->pts, H);
	cvSave(pathToH.c_str(), H);
	delete pts;
}

void BirdsEye::getHFromFile(std::string pathToImg)
{
	H = (CvMat*)cvLoad(pathToImg.c_str());
}

void BirdsEye::changePerspective() {
	IplImage *tmp = cvCreateImage(
			cvGetSize(actualFrame->image),
			actualFrame->image->depth,
			actualFrame->image->nChannels
			);
	cvWarpPerspective(
		actualFrame->image, 
		tmp, 
		H, 
		CV_INTER_LINEAR 
			| CV_WARP_INVERSE_MAP 
			| CV_WARP_FILL_OUTLIERS
		);
	cvReleaseImage(&(actualFrame->image));
	actualFrame->image = tmp;
}

Frame* BirdsEye::getFrame()
{
#ifdef DEBUG_CALLS
	std::cout << "BirdsEye getFrame called.\n";
#endif
	Frame* frame = NULL;
	if(this->actualFrame) frame = new Frame(cvCloneImage(this->actualFrame->image));
	return frame;	
}
void BirdsEye::next(int frameDrop)
{
#ifdef DEBUG_CALLS
	std::cout << "BirdsEye next called.\n";
#endif
	delete actualFrame;
	source->next(frameDrop);
	actualFrame = source->getFrame();
	this->changePerspective();
}

CvRect* BirdsEye::changeRectPerspective(CvRect* rect)
{
	CvRect* rectOut = new CvRect;
	CvPoint pt[4];
	int i;
	float x,y;
	float minx=999999.0,miny=999999.0,maxx=0.0,maxy=0.0;

	pt[0].x=rect->x;
	pt[0].y=rect->y;
	pt[1].x=rect->x+rect->width;
	pt[1].y=rect->y;
	pt[2].x=rect->x;
	pt[2].y=rect->y+rect->height;
	pt[3].x=rect->x+rect->width;
	pt[3].y=rect->y+rect->height;
	
	for(i=0;i<4;i++)
	{
		x = (pt[i].x*CV_MAT_ELEM(*H, float, 0,0) + pt[i].y*CV_MAT_ELEM(*H, float, 0, 1) + CV_MAT_ELEM(*H, float, 0,2)) / (pt[i].x*CV_MAT_ELEM(*H, float, 2,0) + pt[i].y*CV_MAT_ELEM(*H, float, 2,1) + CV_MAT_ELEM(*H, float, 2,2));
		y = (pt[i].x*CV_MAT_ELEM(*H, float, 1,0) + pt[i].y*CV_MAT_ELEM(*H, float, 1,1) + CV_MAT_ELEM(*H, float, 1,2)) / (pt[i].x*CV_MAT_ELEM(*H, float, 2,0) + pt[i].y*CV_MAT_ELEM(*H, float, 2,1) + CV_MAT_ELEM(*H, float, 2,2));
		if(x<minx)minx=x;
		if(y<miny)miny=y;
		if(x>maxx)maxx=x;
		if(y>maxy)maxy=y;
	}

	
	rectOut->x=(int)minx;
	rectOut->y=(int)miny;
	rectOut->width=(int)(maxx-minx);
	rectOut->height=(int)(maxy-miny);

	return rectOut;
}