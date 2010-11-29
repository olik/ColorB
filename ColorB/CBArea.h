/*
 * Class holds information about current area
*/

#ifndef CBAREA_H
#define CBAREA_H

#include "QColor"
#include "CBPixelArea.h"

class CBArea : public CBPixelArea
{

public:
    CBArea()
    {
	color = QColor(0,0,0);
    }
    ~CBArea()
    {
    }

    // Color of the area
protected:
    QColor color;
public:
    QColor GetColor() const { return color; }
    void SetColor(const QColor _color) { color = _color; }

};

#endif // CBAREA_H
