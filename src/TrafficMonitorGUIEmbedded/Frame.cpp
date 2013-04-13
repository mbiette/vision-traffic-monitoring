#include "stdafx.h"
#include "Frame.h"

Frame::Frame(IplImage* img)
{
	this->image=img;
}
Frame::Frame() {
	this->image=NULL;
}
Frame::~Frame()
{
	if(image) cvReleaseImage(&image);
}
void Frame::display( const char* windowName)
{
	cvShowImage(windowName, image);
}
void Frame::threshold(int level)
{
	cvThreshold(this->image, this->image, level, 255, CV_THRESH_BINARY);
}

void Frame::fill()
{
	IplImage *mor = cvCreateImage(cvGetSize(this->image), 8, 1);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;

	if(this->image->nChannels > 1) this->grayScale();

	cvFindContours(this->image, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    cvZero(mor);

	for( ; contour != 0; contour = contour->h_next )
	{
		CvScalar color = CV_RGB( 255, 255, 255 );
		cvDrawContours( mor, contour, color, color, 0, CV_FILLED, 8 );
	}
	cvConvertImage(mor, this->image, 0);

	cvClearMemStorage(storage);
	cvReleaseImage(&mor);
}

void Frame::and(Frame *B)
{
	cvAnd(image,B->image,image);
}

void Frame::or(Frame *B)
{
	cvOr(image,B->image,image);
}

void Frame::xOr(Frame *B)
{
	cvXor(image,B->image,image);
}

void Frame::dilation(int size)
{
	IplConvKernel *kernel = cvCreateStructuringElementEx(size, size, size/2, size/2, CV_SHAPE_RECT);
	cvDilate(image, image, kernel);
	cvReleaseStructuringElement(&kernel);
}

void Frame::erosion(int size)
{
	IplConvKernel *kernel = cvCreateStructuringElementEx(size, size, size/2, size/2, CV_SHAPE_RECT);
	cvErode(image, image, kernel);
	cvReleaseStructuringElement(&kernel);
}

void Frame::diff(Frame *B)
{
	cvAbsDiff(image, B->image, image);
}

void Frame::inv()
{
	cvNot(image,image);
}

void Frame::grayScale()
{
	int flip=0;
	if(image->origin!=IPL_ORIGIN_TL){
		flip=CV_CVTIMG_FLIP;
	}
	IplImage* img_nvg = cvCreateImage(cvGetSize(image), image->depth, 1);
	cvConvertImage(image, img_nvg, flip);
	cvReleaseImage(&image);
	image=img_nvg;
}

void Frame::set(int color) {
	cvSet(image,cvScalarAll(color));
}

double Frame::ratioBW() {
	double w = cvCountNonZero(image);
	double b = ((image->height)*(image->width))-w;
	return w/b;
}

void Frame::operator =(Frame *B)
{
	if(image) cvReleaseImage(&image);
	image = cvCloneImage(B->image);
}
void Frame::operator =(Frame B)
{
	if(image) cvReleaseImage(&image);
	image = cvCloneImage(B.image);
}

