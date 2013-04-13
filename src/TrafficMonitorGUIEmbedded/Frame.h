#ifndef INC_FRAME
#define INC_FRAME

#include "basic.hpp"
#include "opencv.h"

class Frame 
{
	public : 
		//Variables
		IplImage *image;
		
		
		//Constructor
		Frame(IplImage* img);
		Frame();

		//Destructor
		~Frame();

		//Methods
		void display(const char* windowName);
		void threshold(int level);
		void fill();
		void getMor();
		void and(Frame *B);
		void or(Frame *B);
		void xOr(Frame *B);
		void dilation(int size=5);
		void erosion(int size=2);
		void diff(Frame *B);
		void inv();
		void grayScale();
		void set(int color=0);
		double ratioBW();
		void operator =(Frame *B);
		void operator =(Frame B);
		
};

#endif