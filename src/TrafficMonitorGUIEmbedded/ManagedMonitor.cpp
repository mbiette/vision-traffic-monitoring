#include "stdafx.h"
#include "ManagedMonitor.h"
#include "Form1.h"


ManagedMonitor::ManagedMonitor(System::Windows::Forms::Label ^NumBus, System::Windows::Forms::Label ^NumVehicle, System::Windows::Forms::Label ^NumCars, System::Windows::Forms::Label ^NumPed, System::Windows::Forms::Label ^NumUndef, System::Windows::Forms::Label ^StateofTraffic, System::Windows::Forms::Label ^OnRoadSpeed, System::Windows::Forms::TextBox ^BlobOutput)
{
	/*Output Text Arrays*/
	this->FoundObjects = NumVehicle;
	this->MORSpeed = OnRoadSpeed;
	this->nbBus = NumBus;
	this->nbCars = NumCars;
	this->nbPed = NumPed;
	this->TrafState = StateofTraffic;
	this->nbUndef = NumUndef;
	this->InfoBlobs = BlobOutput;
}

ManagedMonitor::~ManagedMonitor()
{
	
}

void ManagedMonitor::UpdateTextOutputs(Merging *Infos)
{
	this->MORSpeed->Text = gcnew System::String(Infos->InfoMORS.c_str());
	this->FoundObjects->Text = gcnew System::String(Infos->InfoVehi.c_str());
	this->nbBus->Text = gcnew System::String(Infos->InfoBus.c_str());
	this->nbCars->Text = gcnew System::String(Infos->InfoCars.c_str());
	this->nbPed->Text = gcnew System::String(Infos->InfoPeds.c_str());
	this->TrafState->Text = gcnew System::String(Infos->InfoTraffic.c_str());
	this->nbUndef->Text = gcnew System::String(Infos->InfoUndef.c_str());
}