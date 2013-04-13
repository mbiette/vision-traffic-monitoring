#include "stdafx.h"
#include "BlobElem.h"


BlobElem::BlobElem(int id, CBlob* blob, BlobElem *next)
{
	double pol[4] = {1,1,1,1};
	/* Infos */	
	this->id = id;
	this->updateBlobInfo(blob, pol, 0, 0);
	this->color = CV_RGB(255,255,255);
	this->meanspeed = 0;
	this->numSpeed = 0;
	this->ratio = blob->GetBoundingBox().height/blob->GetBoundingBox().width;
	this->area = blob->Area();
	this->area2 = blob->Area();
	

	/* Timestamp */
	time( &rawTime );

	/* Tracking timeout */
	this->timeout = 2;
	this->countdown = 10;

	/* Link data */
	this->next = next;
}

void BlobElem::updateBlobInfo(CBlob* blob, double Mat[], int AreaRef1, int AreaRef2) 
{
	Compare classifier;
	
	double objectArea;
	/* Blob Data */
	int Farea;

	double ratioNew = (double)blob->GetBoundingBox().height/(double)blob->GetBoundingBox().width;
	
	Farea = blob->Area();

	
	if((ratioNew/(this->rect.height/this->rect.width)) <= 1.10 && (ratioNew/(this->rect.height/this->rect.width)) >= 0.90 && 0.95*(double)this->area2 <= (double)Farea) 
	{
		objectArea = blob->Area();
		
		this->area = (objectArea + (this->area) * (this->nArea))/(this->nArea+1);
		(this->nArea)++;
		this->type = classifier.object(this->area, AreaRef1, AreaRef2);

		this->meanspeed = abs(((this->meanspeed*this->numSpeed + 3.6*(sqrt(pow(this->x - blob->MaxX(), 2) + pow(this->y - blob->MaxY(), 2))*/*(10.0/88.0)*/abs((double)Mat[1]/(double)Mat[0])*30))/(this->numSpeed+1)));
	
		this->numSpeed++;
		this->xDiff = (this->x - blob->MaxX())/2;
		this->yDiff = (this->y - blob->MaxY())/2;

		this->area2 = Farea;
	}
	this->x = blob->MaxX();
	this->y = blob->MaxY();

	/* Display proprietes */
	this->rect = blob->GetBoundingBox();

	/* Reset the timeout */
	this->timeout = 2;
}

