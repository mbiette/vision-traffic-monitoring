#ifndef INC_BLOBELEM
#define INC_BLOBELEM

#include "BlobResult.h"
#include "Compare.h"
#include <time.h>
#include <string>


class BlobElem {
public:
	BlobElem(int id, CBlob* blob, BlobElem* next = NULL);
	void updateBlobInfo(CBlob* blob, double Mat[4], int AreaRef1, int AreaRef2);
	

	/* Blob Data */
	int id;
	int meanspeed;
	int numSpeed;
	double xDiff;
	double yDiff;
	double x,y;

	/* Display proprietes */
	CvScalar color;
	CvRect rect;
	double area, area2;
	int nArea;
	objectType type;
	double ratio;
	double nRatio;

	/* Timestamp */
	time_t rawTime;

	/* Tracking timeout */
	int timeout;
	int countdown; // Countdown to know if the blob stayed long enough on the video.

	/* Link Data */
	BlobElem* next;
};

#endif