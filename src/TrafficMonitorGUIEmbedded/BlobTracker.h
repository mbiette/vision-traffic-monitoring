#ifndef INC_BLOBTRACKER
#define INC_BLOBTRACKER

#include "basic.hpp"
#include "opencv.h"
#include "Frame.h"
#include "Video.h"
#include "BirdsEye.h"
#include "BlobList.h"
#include "BlobResult.h"
#include <fstream>
using namespace std;

class BlobTracker: public Interface {
private:
	/* Interfaces */
	Interface* blobSrc; // Where we should get the Moving Object Region Frame.
	Interface* videoSrc; // Where we are supposed to get the frame where we should draw the output.
	BirdsEye* birdsEye; // Perspective adjustement if needed.

	/* Frames */
	Frame* MOR;
	Frame* outputFrame;

	/* Wanted Data */
	Points AreaPoints;
	int meanOnroadSpeed;
	int nmeanSpeed;
	int TrafficState;
	string StateOfTraffic;
	int NbTotalBlobs;
	double Mat[4];//Array containing road info as defined hereafter: 0 - length in pixels, 1 - length in meters, 2 - width in pixels, 3 - width in meters
	string PathToDMat;
	BlobList list;


	

	/** Methods **/
	void updateTrackingList(CBlobResult* blobs);
	void getDistanceMat();
	void getDMatFromFile();//Before you ask DMat stands for Distance Matrix!
	void getDMatManually();
	bool isDistanceFileAvailable();
	void computeTrafficState();
	void computemeanOnroadSpeed();
	void generateOutputFrame();

public:
	int getmeanOnroadSpeed();
	int getnBus();
	int getnCars();
	int getnPed();
	int getnUndef();
	int getTrafficState();
	int getTotalElems();
	string getStateOfTraffic();
	BlobTracker(Interface* blobSrc, Interface* videoSrc, BirdsEye* birdsEye, string PathToCopy);
	~BlobTracker();

	Frame* getFrame();
	void next(int frameDrop = 0);
};

#endif