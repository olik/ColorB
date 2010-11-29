/*
 * Class holds information about all pixels of selected color including border
*/

#ifndef CBPIXELAREA_H
#define CBPIXELAREA_H

#include "math.h"
#include "CBPixel.h"
#include "../Common/RMMVArray.h"
#include "../Common/CBUtils.h"

class CBPixelArea
{
public:
    typedef CRMMVArray<CBPixel> PIXELARRAY;

public:
    CBPixelArea()
    {

    }
    ~CBPixelArea()
    {
    }

    // Aray of all pixels in area
protected:
    PIXELARRAY area;
public:
    PIXELARRAY GetArea() { return area; }
protected:
    // Is pixel inside the area
    bool IsPixelInsideTheArea(const CBPixel _pixel) const
    {
	if (area.Find(CBPixel(_pixel.GetX()+1, _pixel.GetY())) == -1) return 0;
	if (area.Find(CBPixel(_pixel.GetX()-1, _pixel.GetY())) == -1) return 0;
	if (area.Find(CBPixel(_pixel.GetX(), _pixel.GetY()+1)) == -1) return 0;
	if (area.Find(CBPixel(_pixel.GetX(), _pixel.GetY()-1)) == -1) return 0;
	return 1;
    }
    // Update border removing all non-border pixels
public:
    void UpdateBorderPixels()
    {
	for (int areaIndex = 0; areaIndex < area.GetCount(); areaIndex++)
	{
	    CBPixel pixel = area.GetAt(areaIndex);
	    if (IsPixelInsideTheArea(pixel)) RemoveBorderPixel(pixel);
	    else border.AddUnique(pixel);
	}
    }

    // Array of all border's pixels in area
protected:
    PIXELARRAY border;
public:
    PIXELARRAY GetBorder() { return border; }
public:
    bool IsPixelOnTheBorder(const CBPixel _pixel) const
    {
	for (int borderIndex = 0; borderIndex < border.GetCount(); borderIndex++)
	{
	    if (_pixel == border.GetAt(borderIndex)) return true;
	}
	return false;
    }
    bool IsPixelAtTheBorder(const CBPixel _pixel) const
    {
	int borderPixelCount = (int)IsPixelOnTheBorder(CBPixel(_pixel.GetX()+1, _pixel.GetY())) +
			       (int)IsPixelOnTheBorder(CBPixel(_pixel.GetX()-1, _pixel.GetY())) +
			       (int)IsPixelOnTheBorder(CBPixel(_pixel.GetX(), _pixel.GetY()+1)) +
			       (int)IsPixelOnTheBorder(CBPixel(_pixel.GetX(), _pixel.GetY()-1));
	return borderPixelCount;
    }

    // Array of all areas this area can dominate
protected:
    CRMMVArray<CBPixelArea*> dominateAreas;
public:
    void AddDominateArea(CBPixelArea * dominateArea)
    {
	dominateAreas.Add(dominateArea);
    }

    // Add pixel to area border
public:
    void AddPixel(CBPixel pixel)
    {
	area.Add(pixel);
	border.Add(pixel);
    }
    void RemovePixel(const CBPixel _pixel)
    {
	RemoveBorderPixel(_pixel);
	RemoveAreaPixel(_pixel);
    }
    void RemoveAreaPixel(const CBPixel _pixel)
    {
	int areaIndex = area.Find(_pixel);
	if (areaIndex != -1) area.RemoveAt(areaIndex);
    }
    void RemoveBorderPixel(const CBPixel _pixel)
    {
	int borderIndex = border.Find(_pixel);
	if (borderIndex != -1) border.RemoveAt(borderIndex);
    }

    // Is area still exist
public:
    bool IsAreaExists() const { return area.GetCount(); }

    // Dominate pixel
public:
    bool Dominate()
    {
	// For each area we dominate
	for (int areaIndex = 0; areaIndex < dominateAreas.GetCount(); areaIndex++)
	{
	    // Select one area
	    CBPixelArea * dominateArea = dominateAreas.GetAt(areaIndex);

	    // if area does not exist remove it
	    if (!dominateArea->IsAreaExists())
	    {
		dominateAreas.RemoveAt(areaIndex);
		areaIndex--;
		continue;
	    }

	    // Dominate current area
	    if (DominateArea(dominateArea))
	    {
		return 1;
	    }
	}
	return 0;
    }

    // Dominate current area
    bool DominateArea(CBPixelArea * dominateArea)
    {
	CBPixel activePixel;
	if (!ActivateOnePixel(dominateArea, &activePixel)) return 0;
	//
	CBPixel enemyPixel = SelectOnePixelToDominate(dominateArea, activePixel);
	dominateArea->RemovePixel(enemyPixel);
	AddPixel(enemyPixel);
	UpdateBorderPixels();
	dominateArea->UpdateBorderPixels();
	//
	return 1;
    }

    // Activate one of pixel
protected:
    bool ActivateOnePixel(CBPixelArea * dominateArea, CBPixel * _pixel) const
    {
	CRMMVArray<CBPixel> activePixels;
	for (int borderIndex = 0; borderIndex < border.GetCount(); borderIndex++)
	{
	    CBPixel pixel = border.GetAt(borderIndex);
	    if (dominateArea->IsPixelAtTheBorder(pixel)) activePixels.Add(pixel);
	}
	if (activePixels.GetCount())
	{
	    *_pixel = activePixels.GetAt(CBUtils::Random(activePixels.GetCount()));
	    return 1;
	}
	return 0;
    }

    // Select one pixel to dominate
protected:
    CBPixel SelectOnePixelToDominate(CBPixelArea * dominateArea, const CBPixel _pixel)
    {
	CRMMVArray<CBPixel> activeBorder;
	if (dominateArea->IsPixelOnTheBorder(CBPixel(_pixel.GetX()+1, _pixel.GetY()))) activeBorder.Add(CBPixel(_pixel.GetX()+1, _pixel.GetY()));
	if (dominateArea->IsPixelOnTheBorder(CBPixel(_pixel.GetX()-1, _pixel.GetY()))) activeBorder.Add(CBPixel(_pixel.GetX()-1, _pixel.GetY()));
	if (dominateArea->IsPixelOnTheBorder(CBPixel(_pixel.GetX(), _pixel.GetY()+1))) activeBorder.Add(CBPixel(_pixel.GetX(), _pixel.GetY()+1));
	if (dominateArea->IsPixelOnTheBorder(CBPixel(_pixel.GetX(), _pixel.GetY()-1))) activeBorder.Add(CBPixel(_pixel.GetX(), _pixel.GetY()-1));

	return activeBorder.GetAt(CBUtils::Random(activeBorder.GetCount()));
    }

};

#endif // CBPIXELAREA_H
