#include "stdafx.h"
#include "BlobTracker.h"


BlobTracker::BlobTracker(Interface* blobSrc, Interface* videoSrc, BirdsEye* birdsEye, std::string PathToCopy){
	this->blobSrc = blobSrc;
	this->videoSrc = videoSrc;
	this->birdsEye = birdsEye;
	this->MOR = NULL;
	this->outputFrame = NULL;
	this->PathToDMat = PathToCopy;
	this->list.PathToArea = PathToCopy;
	this->list.PathToArea.append(".area");
	this->PathToDMat.append(".dmat");
	this->getDistanceMat();
	this->NbTotalBlobs=0;
	this->TrafficState = 0;
	this->meanOnroadSpeed = 0;
	this->nmeanSpeed = 0;
	this->next();
}

BlobTracker::~BlobTracker() {
	delete MOR;
	delete outputFrame;
	this->MOR = NULL;
	this->outputFrame = NULL;
}

void BlobTracker::next(int frameDrop) {
	/* Blob Detection */
	if(MOR) delete MOR;
	blobSrc->next(frameDrop);
	MOR = blobSrc->getFrame();
	
	CBlobResult blobs(MOR->image, NULL, 0);
	blobs.Filter(blobs, B_EXCLUDE, CBlobGetArea(), B_LESS, 100); //Filtering blobs that are too small.

	/* Blob Tracking */
	updateTrackingList(&blobs);

	/*Data collecting*/
	this->computemeanOnroadSpeed();

	/* Generating output frame */
	if(outputFrame) delete outputFrame;
	outputFrame = videoSrc->getFrame();

	generateOutputFrame();
}


Frame* BlobTracker::getFrame() {
	Frame* out = new Frame();
	*out = outputFrame;
	return out;
}

void BlobTracker::updateTrackingList(CBlobResult* blobs) {
	BlobElem* closestBlobElem = NULL;
	CBlob* ptBlobList = NULL;

	list.updateElemsTimeoutAndType();

	for(int i=0;i<blobs->GetNumBlobs();i++)
	{
		ptBlobList = blobs->GetBlob(i);
		closestBlobElem = list.getClosestBlob(ptBlobList->MaxX(),ptBlobList->MaxY(),27);
		if(closestBlobElem == NULL)
		{
			list.addBlob(ptBlobList);
		}
		else
		{
			closestBlobElem->updateBlobInfo(ptBlobList, this->Mat, list.AreaRef1, list.AreaRef2);
		}
	}

	this->NbTotalBlobs = list.clearTimeoutElems(this->NbTotalBlobs);
}

void BlobTracker::generateOutputFrame() {
	list.jumpToStart();
	CvRect* rect = list.getLastElemRect();
	CvRect* rectBirdsEye;
	CvScalar* rectColor;
	CvPoint p1,p2;

	while(rect)
	{
		rectBirdsEye = this->birdsEye->changeRectPerspective(rect);
		rectColor = list.getLastElemColor();
		p1.x = rectBirdsEye->x;
		p1.y = rectBirdsEye->y;
		p2.x = rectBirdsEye->x + rectBirdsEye->width;
		p2.y = rectBirdsEye->y + rectBirdsEye->height;
		if(list.isLastElemDrawable())
		{
			cvRectangle(outputFrame->image,p1,p2,*rectColor, 3);
		}

		delete rectBirdsEye;

		list.goToNext();
		rect = list.getLastElemRect();
	}
}

void BlobTracker::computeTrafficState()
{
	double Traffic;
	Traffic = abs(((2*this->list.getnbBus()+this->list.getnbCars()+0.5*this->list.getnbPed()))*7.0/((this->MOR->image->height*0.33*(this->MOR->image->width))*(this->Mat[1]*(this->Mat[3])/(this->Mat[0]*(this->Mat[2])))));
	this->TrafficState = Traffic*1000;
	
	if( this->TrafficState < 40 ) this->StateOfTraffic = "Fluid";
	else if( this->TrafficState < 70 ) this->StateOfTraffic = "Heavy";
	else if( this->TrafficState < 85 ) this->StateOfTraffic = "Charged";
	else this->StateOfTraffic = "Overloaded";
}

void BlobTracker::computemeanOnroadSpeed()
{
	int meanSpeed = 0;
	int correct = 0;
	int speed = 0, members = 0;
	list.jumpToStart();
	
	do
	{
		meanSpeed += speed;
		speed = this->list.getLastElemSpeed();
		if(speed == 0) correct++;
		list.goToNext();
	}while(speed!=-1);
	members = this->list.getnumElem() - correct;
	if(members!=0)meanSpeed = meanSpeed/members;
	this->meanOnroadSpeed = meanSpeed;
	this->computeTrafficState();
}

bool BlobTracker::isDistanceFileAvailable()
{
	struct stat stFileInfo; 
	bool blnReturn; 
	int intStat;

	intStat = stat(this->PathToDMat.c_str(),&stFileInfo);
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

void BlobTracker::getDistanceMat()
{
	if(this->isDistanceFileAvailable()) this->getDMatFromFile();
	else
	{
		std::cout<<endl<<"No Distance file found. Please enter the distances manually"<<endl;
		this->getDMatManually();
	}
}

void BlobTracker::getDMatManually()
{
	Frame* tmpFrame = NULL;
	tmpFrame = this->birdsEye->getFrame();
	std::cout<<endl<<"Please select a reference width and length for which you KNOW the distances"<<endl;
	this->AreaPoints.getPointsFromMouse("Select the reference points", tmpFrame->image);
	this->Mat[0] = this->AreaPoints.pts[1].y - this->AreaPoints.pts[0].y;
	this->Mat[2] = this->AreaPoints.pts[3].x - this->AreaPoints.pts[2].x;
	std::cout<<"Now enter the length in meters : ";
	std::cin>>this->Mat[1];
	std::cout<<endl<<"And the width : ";
	std::cin>>this->Mat[3];
	ofstream Dist( this->PathToDMat.c_str(), ios::out|ios::trunc);
	if(Dist)
	{
		Dist<<this->Mat[0]<<" "<<this->Mat[1]<<" "<<this->Mat[2]<<" "<<this->Mat[3];
		Dist.close();
	}
	else std::cout<<endl<<"Impossible to create the file : "<<this->PathToDMat<<" Distance informations will not be saved"<<endl;
	cvDestroyWindow("Select the reference points");
}

void BlobTracker::getDMatFromFile()
{
	ifstream Dist(this->PathToDMat.c_str(), ios::in);
	if(Dist) Dist>>this->Mat[0]>>this->Mat[1]>>this->Mat[2]>>this->Mat[3];
	else
	{
		std::cout<<endl<<"Impossible to open file : "<<this->PathToDMat<<" Please enter distance informations manually"<<endl;
		this->getDMatManually();
	}
}


int BlobTracker::getTotalElems()
{
	return this->NbTotalBlobs;
}

int BlobTracker::getTrafficState()
{
	return this->TrafficState;
}

int BlobTracker::getnUndef()
{
	return this->list.getnumUndef();
}

int BlobTracker::getnPed()
{
	return this->list.getnumPed();
}

int BlobTracker::getnCars()
{
	return this->list.getnumCars();
}

int BlobTracker::getnBus()
{
	return this->list.getnumBus();
}

int BlobTracker::getmeanOnroadSpeed()
{
	return this->meanOnroadSpeed;
}

string BlobTracker::getStateOfTraffic()
{
	return this->StateOfTraffic;
}