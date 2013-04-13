#ifndef MANAGEDMONITOR_H_INCLUDED
#define MANAGEDMONITOR_H_INCLUDED

#include "Merging.h"

public ref class ManagedMonitor
{/*A Class created because all the forms handler and operations need to be done inside a manged C++ Class
 So here it is !*/
	public:
		System::Windows::Forms::Label^ FoundObjects;
		System::Windows::Forms::Label^ MORSpeed;
		System::Windows::Forms::Label^ TrafState;
		System::Windows::Forms::Label^ nbCars;
		System::Windows::Forms::Label^ nbBus;
		System::Windows::Forms::Label^ nbUndef;
		System::Windows::Forms::Label^ nbPed;
		System::Windows::Forms::TextBox^ InfoBlobs;
		void UpdateTextOutputs(Merging* Infos);
		ManagedMonitor(System::Windows::Forms::Label^ NumBus, System::Windows::Forms::Label^ NumVehicle, System::Windows::Forms::Label^ NumCars, System::Windows::Forms::Label^ NumPed, System::Windows::Forms::Label^ NumUndef, System::Windows::Forms::Label^ TrafficState, System::Windows::Forms::Label^ OnRoadSpeed, System::Windows::Forms::TextBox^ BlobOutput);
		~ManagedMonitor();
};

#endif