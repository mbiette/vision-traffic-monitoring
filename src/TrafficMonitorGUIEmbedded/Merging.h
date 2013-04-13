#ifndef MERGING_H_INCLUDED
#define MERGING_H_INCLUDED

#include "main.h"


class Merging
{
	public:
		Video* video;
		int nFoundObjects;
		int MeanOnRoadSpeed;
		int TrafficState;
		int nCars;
		int nBuses;
		int nPedestrians;
		int nUndefined;
		int VideoEnd;
		string InfoMORS;
		string InfoBus;
		string InfoVehi;
		string InfoCars;
		string InfoPeds;
		string InfoUndef;
		string InfoTraffic;
		string outblob;
		string outputs;
		void OutputInfos();
		Merging();
		~Merging();
		void Run();
		void UpdateInfos();
		void changeVideo(string VideoPath);

	private:
		Frame* OutputVideo;
		Frame* OutputTracker;
		string PathToVideo;
		BirdsEye* birdsEye;
		Background* background;
		BlobTracker* tracker;
		bool Work;
		
		
};

#endif