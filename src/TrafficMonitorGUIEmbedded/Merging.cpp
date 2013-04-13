#include "stdafx.h"
#include "Merging.h"

void Merging::OutputInfos()
{
	this->UpdateInfos();
	ostringstream Infomors(ostringstream::out);
	ostringstream Infobus(ostringstream::out);
	ostringstream Infocars(ostringstream::out);
	ostringstream Infopeds(ostringstream::out);
	ostringstream Infoundef(ostringstream::out);
	ostringstream Infovehi(ostringstream::out);
	
	Infomors<<this->MeanOnRoadSpeed<<" km/h";
	Infobus<<this->nBuses;
	Infocars<<this->nCars;
	Infopeds<<this->nPedestrians;
	Infoundef<<this->nUndefined;
	Infovehi<<this->nFoundObjects;

	this->InfoMORS = Infomors.str();
	this->InfoBus = Infobus.str();
	this->InfoCars = Infocars.str();
	this->InfoPeds = Infopeds.str();
	this->InfoTraffic = this->tracker->getStateOfTraffic();
	this->InfoUndef = Infoundef.str();
	this->InfoVehi = Infovehi.str();
}

void Merging::UpdateInfos()
{
	this->MeanOnRoadSpeed = this->tracker->getmeanOnroadSpeed();
	this->nBuses = this->tracker->getnBus();
	this->nCars = this->tracker->getnCars();
	this->nPedestrians = this->tracker->getnPed();
	this->nUndefined = this->tracker->getnUndef();
	this->TrafficState = this->tracker->getTrafficState();
	this->nFoundObjects = this->tracker->getTotalElems();
}

Merging::Merging()
{
	/*Arrays*/
	this->background = NULL;
	this->birdsEye = NULL;
	this->tracker = NULL;
	this->video = NULL;
	this->OutputTracker = NULL;
	this->OutputVideo = NULL;

	/*Output Data*/
	this->MeanOnRoadSpeed = 0;
	this->nBuses = 0;
	this->nCars = 0;
	this->nFoundObjects = 0;
	this->nPedestrians = 0;
	this->nUndefined = 0;
	this->TrafficState = 0;
	
	/*Management Data*/
	this->Work = false;
}

Merging::~Merging()
{
	if(this->background) delete this->background;
	if(this->birdsEye) delete this->birdsEye;
	if(this->tracker) delete this->tracker;
	if(this->video) delete this->video;
}

void Merging::changeVideo(string VideoPath)
{
	this->PathToVideo = VideoPath;
	this->Work = true;
	this->VideoEnd = 0;
	if(this->video)
	{
		cvDestroyAllWindows();
		delete this->video;
		this->video = NULL;
		delete this->background;
		this->background = NULL;
		delete this->birdsEye;
		this->birdsEye = NULL;
		delete this->tracker;
		this->tracker = NULL;
	}
}

void Merging::Run() 
{	
	
	if(this->video == NULL) 
	{
		this->video = new Video(this->PathToVideo.c_str());
		this->birdsEye = new BirdsEye(video,this->PathToVideo.c_str());
		this->background = new Background(birdsEye);
		this->tracker = new BlobTracker(background, video, birdsEye, this->PathToVideo.c_str());
	}
	int key = 0;
	

	if(this->video && this->Work)
	{
		this->OutputInfos();
		this->OutputTracker = this->tracker->getFrame();
		this->OutputTracker->display("2-Tracker Output");
		delete this->OutputTracker;
		this->tracker->next();
		this->VideoEnd = 100*cvGetCaptureProperty(video->stream, CV_CAP_PROP_POS_AVI_RATIO);
	}
	
	

	if(this->VideoEnd > 96)
	{
		cvDestroyAllWindows();
		this->Work = false;
		delete this->video;
		this->video = NULL;
		delete this->background;
		this->background = NULL;
		delete this->birdsEye;
		this->birdsEye = NULL;
		delete this->tracker;
		this->tracker = NULL;

	}

	int i;
}
