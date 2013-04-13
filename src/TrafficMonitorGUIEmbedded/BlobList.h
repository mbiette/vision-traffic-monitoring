#ifndef INC_BLOBLIST
#define INC_BLOBLIST

#include "basic.hpp"
#include "BlobResult.h"
#include "BlobElem.h"
#include "Compare.h"
#include "BirdsEye.h"
#include <time.h>
#include <fstream>

class BlobList {
private:
	BlobElem* list;

	int nElem;
	int nCars;
	int nbCars;
	int nBus;
	int nbBus;
	int nPed;
	int nbPed;
	int nUndef;
	int nbUndef;
	int key;
	bool Area1, Area2;
	double areaPedestrian, areaCar, areaBus, areaUndefined;
	int compteur0, compteur1, compteur2, compteur3;
	ofstream fichier;

	void getArea();
	bool isAreaFileAvailable();
	void getAreaFromUser();
	void getAreaFromFile();
	int VALUE;

	/*** Fast Access to elem 
	  * We keep track of the last blob reached in the list
	  * and his parent to be able to do a fast delete.
	 ***/
	BlobElem* prevLastElem;
	BlobElem* lastElem;
	BlobElem* nextLastElem;
public:
	BlobList();
	~BlobList();

	double AreaRef1, AreaRef2;
	void addBlob(CBlob* blob);
	BlobElem* getClosestBlob(double x, double y, double distanceMax);
	void delLastBlob(BlobElem* checkBlob);
	void updateElemsTimeoutAndType();
	int clearTimeoutElems(int x);
	int getnumElem();
	int getnumCars();
	int getnumUndef();
	int getnumBus();
	int getnumPed();
	int getnbCars();
	int getnbBus();
	int getnbPed();
	int getnbUndef();
	string PathToArea;
	void jumpToStart();
	void goToNext();

	CvRect* getLastElemRect();
	int getLastElemSpeed();
	CvScalar* getLastElemColor();
	int getLastElemID();
	bool isLastElemDrawable();
};

#endif