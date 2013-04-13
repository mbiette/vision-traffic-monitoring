#include "stdafx.h"
#include "Background.h"

Background::Background(Interface* source) {
	this->source = source;
	this->currentFrame = NULL;
	this->backgroundExtraction();

	source->next();
	currentFrame = source->getFrame();
	currentFrame->grayScale();
	this->backgroundSubtractionAndUpdate();
}

Background::~Background() {
	
}

void Background::backgroundExtraction() {
	static const int	FRAMEDROP = 20;
	static const int	THRESHOLD = 30;
	static const int	DILATION = 6;
	static const int	EROSION = 4;
	static const double PRECISION = 0.0001; //This is Result of 30/(750*400)

	int loop=0;
	
	Frame *c1, *c2;

	//Loop initialization
	source->next(FRAMEDROP);
	c2 = source->getFrame();
	c2->grayScale();
	
	Frame *ef = new Frame(cvCreateImage(cvGetSize(c2->image), c2->image->depth, 1));//ef.image = cvCreateImage(cvGetSize(c2), c2->depth, 1);
		
	actualBackground.image = cvCreateImage(cvGetSize(c2->image), c2->image->depth, c2->image->nChannels);
	
	ef->set(255);// ef = image blanche 
	
	actualBackground.set(255);// b  = image blanche
	
	do {
		c1=c2;
		source->next(FRAMEDROP); c2 = source->getFrame(); c2->grayScale();
		c1->diff(c2);//d
		c1->threshold(THRESHOLD);//db
		c1->dilation(DILATION);//dlt
		c1->fill();//mor

		c1->inv(); c1->and(ef);//eta
		ef->xOr(c1);//ef
		c1->inv(); c1->or(c2);//bAdd

		actualBackground.and(c1);//b
		
		loop++;

		delete c1;
	} while(ef->ratioBW() > PRECISION);

	delete c2;
	delete ef;
}

void Background::backgroundSubtractionAndUpdate() {
	static const int THRESHOLD=30;
	static const int EROSION=20;
	static const int DILATION=20;

	// Soustraction
	Frame c;
	c = currentFrame;
	
	// Output image
	currentFrame->diff(&actualBackground);
	
	// Update
	currentFrame->threshold(THRESHOLD);
	currentFrame->dilation(DILATION);
	currentFrame->fill();
	currentFrame->erosion(EROSION);
	
	cvCopy(actualBackground.image,c.image,currentFrame->image);
	
	cvAddWeighted(actualBackground.image,0.9, c.image,0.1, 0.0, actualBackground.image);
}

Frame* Background::getFrame() {
#ifdef DEBUG_CALLS
	std::cout << "Background getFrame called.\n";
#endif
	Frame* out = new Frame();
	*out = currentFrame;
	return out;
}


void Background::next(int frameDrop) {
#ifdef DEBUG_CALLS
	std::cout << "Background next called.\n";
#endif
	delete currentFrame;
	source->next(frameDrop);
	currentFrame = source->getFrame();
	currentFrame->grayScale();
	this->backgroundSubtractionAndUpdate();
}