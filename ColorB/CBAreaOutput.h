#ifndef CBAREAOUTPUT_H
#define CBAREAOUTPUT_H

#include "QPainter"
#include "boost/format.hpp"
#include "CBArea.h"

class CBAreaOutput : public CBArea
{
public:
    CBAreaOutput()
    {
    }

public:
    std::string ToString()
    {
	std::string areaString = str ( boost::format("Area(%i) = ") % GetArea().GetCount() );
	for (int i = 0; i < GetArea().GetCount(); i++)
	{
	    areaString += GetArea().GetAt(i).ToString();
	    areaString += " ";
	}
	areaString += "\r\n";

	std::string borderString = str ( boost::format("Border(%i) = ") % GetBorder().GetCount() );
	for (int i = 0; i < GetBorder().GetCount(); i++)
	{
	    borderString += GetBorder().GetAt(i).ToString();
	    borderString += " ";
	}
	borderString += "\r\n";

	return (areaString + borderString);
    }

public:
    void DrawArea(QWidget * parent)
    {
	QPainter painter(parent);
	Qt::PenCapStyle cap = Qt::PenCapStyle(Qt::FlatCap);
	Qt::PenJoinStyle join = Qt::PenJoinStyle(Qt::MiterJoin);
	Qt::PenStyle style =  Qt::PenStyle(Qt::SolidLine);
	painter.setPen(QPen(GetColor(), 1, style, cap, join));

	for (int i = 0; i < GetArea().GetCount(); i++)
	{
	    painter.drawPoint(QPoint(GetArea().GetAt(i).GetX(), GetArea().GetAt(i).GetY()));
	}
    }
};

#endif // CBAREAOUTPUT_H
