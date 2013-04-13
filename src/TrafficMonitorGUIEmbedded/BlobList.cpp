#include "stdafx.h"
#include "BlobList.h"


BlobList::BlobList() {
	list=NULL;

	nElem = 0;
	key = 0;

	prevLastElem=NULL;
	lastElem=NULL;
	nextLastElem=NULL;
	this->Area1 = false;
	this->Area2 = false;
	this->nBus = 0;
	this->nCars = 0;
	this->nPed = 0;
	this->nUndef = 0;
	this->AreaRef1 = 0;
	this->AreaRef2 = 0;
	this->compteur0=0;
	this->compteur1=0;
	this->compteur2=0;
	this->compteur3=0;
	this->nbBus = 0;
	this->nbCars = 0;
	this->nbUndef = 0;
	this->nbPed = 0;
	this->areaCar=0;
	this->areaPedestrian=0;
	this->areaBus=0;
	this->areaUndefined=0;
}

BlobList::~BlobList() {
	prevLastElem = NULL;	
	lastElem = list;
	if(lastElem != NULL) nextLastElem=lastElem->next;

	while(lastElem!=NULL)
	{
			this->delLastBlob(lastElem);
	}
}

void BlobList::addBlob(CBlob* blob) {
	lastElem = new BlobElem(key,blob,list);
	nextLastElem = list;
	prevLastElem = NULL;

	list = lastElem;

	key++;
	nElem++;
}

BlobElem* BlobList::getClosestBlob(double x, double y, double distanceMax) {
	this->jumpToStart();

	bool found = false;

	while(lastElem!=NULL && found!=true)
	{
		if(	sqrt(
				pow( (lastElem->x)-x ,2) + pow( (lastElem->y)-y ,2)
				) <= distanceMax)
		{
			found = true;
		}
		else
		{
			this->goToNext();
		}
	}
	if(found) return lastElem;
	else return NULL;
}

void BlobList::delLastBlob(BlobElem *checkBlob) {
	switch(checkBlob->type)
		{
			case PEDESTRIAN: this->nPed++; break;
			case BUS: this->nBus++; break;
			case CAR: this->nCars++; break;
			case UNDEFINED: this->nUndef++; break;
		}
	if(prevLastElem == NULL)
	{
		/* We have to delete the first element. */
		if(lastElem==list && checkBlob==list && lastElem!=NULL)
		{

			delete list;
			list = nextLastElem;
			lastElem = nextLastElem;
			if (lastElem != NULL) nextLastElem = lastElem->next;
			nElem--;
		}
	}
	else
	{
		if(lastElem==checkBlob && lastElem != NULL){
			delete lastElem;
			prevLastElem->next = nextLastElem;
			lastElem = nextLastElem;
			if (lastElem != NULL) nextLastElem = lastElem->next;
			nElem--;
		}
	}
}

void BlobList::updateElemsTimeoutAndType() {
	
	this->jumpToStart();
	this->nbBus = 0;
	this->nbCars = 0;
	this->nbUndef = 0;
	this->nbPed = 0;

	while(lastElem!=NULL)
	{
		lastElem->timeout--;
		if(lastElem->countdown>0)lastElem->countdown--;
		
		switch(lastElem->type)
		{
			case PEDESTRIAN: lastElem->color = CV_RGB(255, 0, 0); this->nbPed++; break;
			case BUS: lastElem->color = CV_RGB(0, 255, 0); this->nbBus++; break;
			case CAR: lastElem->color = CV_RGB(0, 0, 255); this->nbCars++; break;
			case UNDEFINED: lastElem->color = CV_RGB(255, 255, 255); this->nbUndef++; break;
		}
		this->goToNext();
	}
}

int BlobList::clearTimeoutElems(int NbTotalBlobs) {
	this->jumpToStart();
	char* textTime;
	char* type[] = { {"Pedestrian"}, {"Light"}, {"Heavy"}, {"Undefined"} };
	Compare comparatator;
	
	if (this->isAreaFileAvailable()) this->getAreaFromFile();

	while(lastElem!=NULL)
	{
		if(lastElem->timeout==0)
		{
			if(lastElem->countdown==0)
			{
				textTime = ctime(&lastElem->rawTime);
				NbTotalBlobs++;
			}

			/* Then delete it */
			if(!this->Area1 && !this->Area2) this->getArea();
			this->delLastBlob(lastElem);		
		}
		else
		{
			this->goToNext();
		}
		
		
	}
	
	return NbTotalBlobs;
}

void BlobList::jumpToStart() {
	prevLastElem = NULL;	
	lastElem = list;
	if(lastElem != NULL) nextLastElem=lastElem->next;
}

void BlobList::goToNext() {
	prevLastElem = lastElem;
	lastElem = nextLastElem;
	if(lastElem != NULL) nextLastElem=lastElem->next;
}

CvRect* BlobList::getLastElemRect() {
	if(lastElem) return &(lastElem->rect);
	else return NULL;
}

CvScalar* BlobList::getLastElemColor() {
	if(lastElem) return &(lastElem->color);
	else return NULL;
}

int BlobList::getLastElemSpeed() {
	if(lastElem) return lastElem->meanspeed;
	else return -1;
}

int BlobList::getLastElemID() {
	if(lastElem) return lastElem->id;
	else return -1;
}

int BlobList::getnumElem()
{
	return this->nElem;
}

int BlobList::getnumCars()
{
	return this->nCars;
}

int BlobList::getnumBus()
{
	return this->nBus;
}

int BlobList::getnumPed()
{
	return this->nPed;
}

int BlobList::getnumUndef()
{
	return this->nUndef;
}

int BlobList::getnbCars()
{
	return this->nbCars;
}

int BlobList::getnbBus()
{
	return this->nbBus;
}

int BlobList::getnbPed()
{
	return this->nbPed;
}

int BlobList::getnbUndef()
{
	return this->nbUndef;
}

bool BlobList::isLastElemDrawable()
{
	return (this->lastElem->countdown==0)? TRUE:FALSE;
}

bool BlobList::isAreaFileAvailable()
{
	struct stat stFileInfo; 
	bool blnReturn; 
	int intStat;

	intStat = stat(this->PathToArea.c_str(),&stFileInfo);
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


void BlobList::getArea()
{
	if(this->isAreaFileAvailable()) this->getAreaFromFile();
	else
	{
		std::cout<<endl<<"No area file found. Please enter the types of vehicles you see in order to know the average areas of each types"<<endl;
		this->getAreaFromUser();
	}
}

void BlobList::getAreaFromUser()
{	
	std::cout<<"Please enter : 0 for pedestrian, 1 for light vehicle, 2 for heavy vehicle or 3 if you can not define it : ";
	std::cin>>this->VALUE;
	
	switch(this->VALUE)
	{
		case 0: this->compteur0++;
				this->areaPedestrian = (lastElem->area + this->areaPedestrian)/this->compteur0;
				break;
		case 1:	this->compteur1++;
				this->areaCar = (lastElem->area + this->areaCar)/this->compteur1;	
				break;
		case 2: compteur2++;
				this->areaBus = (lastElem->area + this->areaBus)/this->compteur2;
				break;
		case 3:	compteur3++;
				this->areaUndefined = (lastElem->area + this->areaUndefined)/this->compteur3;
				break;
	}
	if (this->VALUE == 3)
	{
		compteur3++;
		this->areaUndefined = (lastElem->area + this->areaUndefined)/this->compteur3;
	}



	if (this->compteur0>=1 && this->compteur1>=1)
	{
		this->AreaRef1 = (this->areaPedestrian + this->areaCar)/2.0;
		this->AreaRef2 = this->AreaRef1*7.0;
		this->Area1 = true;
		this->Area2 = true;

		ofstream areaFile(this->PathToArea.c_str(), ios::out|ios::trunc);
		if(areaFile)  // si l'ouverture a fonctionné
		{
				areaFile << this->AreaRef1 << " " << this->AreaRef2;  // on met dans "contenu" la ligne
				areaFile.close();
		}
		else
			std::cout << "Impossible d'ouvrir le fichier !" << endl;
	}
	if (this->compteur1>=1 && this->compteur2>=1)
	{
		this->AreaRef2 = (1.35*this->areaCar + 1.5*this->areaBus)/2.0;
		this->AreaRef1 = this->AreaRef2/7.0;
		this->Area1 = true;
		this->Area2 = true;

		ofstream areaFile(this->PathToArea.c_str(), ios::out|ios::trunc);
		if(areaFile)  // si l'ouverture a fonctionné
		{
				areaFile << this->AreaRef1 << " " << this->AreaRef2;  // on met dans "contenu" la ligne
				areaFile.close();
		}
		else
			std::cout << "Impossible d'ouvrir le fichier !" << endl;
	}
}

void BlobList::getAreaFromFile()
{
	ifstream areaFile(this->PathToArea.c_str(), ios::in);
	if(areaFile) areaFile >> this->AreaRef1 >> this->AreaRef2;
	else
	{
		std::cout<<endl<<"Impossible to open file : "<<this->PathToArea<<" Please enter the type of vehicle you see"<<endl;
		this->getAreaFromUser();
	}
}