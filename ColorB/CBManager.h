/*
 * Class creates and controls all areas
*/

#ifndef CBMANAGER_H
#define CBMANAGER_H

#include "CBArea.h"
#include "../Common/RMMVArray.h"

class CBManager
{
public:
    CBManager()
    {
	currentStep = 0;
	CreateAllAreas();
    }

    // Current step
protected:
    int currentStep;
public:
    void NextStep()
    {
	areas.GetAt(currentStep)->Dominate();
	currentStep++;
	if (currentStep == areas.GetCount()) currentStep = 0;
    }

    // All areas
protected:
    CRMMVArray<CBArea*> areas;

    // Print areas
public:
    std::string ToString() const
    {
	char infoString[128];
	sprintf(infoString, "X=%i Red=%i Green=%i Blue=%i", areas.GetAt(0), areas.GetAt(1), areas.GetAt(2));
	std::string infoStdString = infoString;
	return infoStdString;
    }

    // Create all areas
protected:
    void CreateAllAreas()
    {
	CBArea * areaX = new CBArea;
	for (int x = 0; x < 60; x++)
	{
	    for (int y = 0; y < 20; y++)
	    {
		areaX->AddPixel(CBPixel(x,y));
	    }
	}
	for (int x = 0; x < 20; x++)
	{
	    for (int y = 20; y < 40; y++)
	    {
		areaX->AddPixel(CBPixel(x,y));
	    }
	}
	for (int x = 40; x < 60; x++)
	{
	    for (int y = 20; y < 40; y++)
	    {
		areaX->AddPixel(CBPixel(x,y));
	    }
	}
	for (int x = 0; x < 60; x++)
	{
	    for (int y = 40; y < 60; y++)
	    {
		areaX->AddPixel(CBPixel(x,y));
	    }
	}
	areaX->UpdateBorderPixels();

	CBArea * areaRed = new CBArea;
	areaRed->AddPixel(CBPixel(10,50));
	areaRed->AddDominateArea(areaX);

	CBArea * areaGreen = new CBArea;
	areaGreen->AddPixel(CBPixel(50,50));
	areaGreen->AddDominateArea(areaX);

	CBArea * areaBlue = new CBArea;
	areaBlue->AddPixel(CBPixel(30,10));
	areaBlue->AddDominateArea(areaX);

	areaRed->AddDominateArea(areaGreen);
	areaGreen->AddDominateArea(areaBlue);
	areaBlue->AddDominateArea(areaRed);

	areas.Add(areaX);
	areas.Add(areaRed);
	areas.Add(areaGreen);
	areas.Add(areaBlue);
    }
};

#endif // CBMANAGER_H
