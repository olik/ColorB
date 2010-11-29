#ifndef CBAREAOUTPUT_H
#define CBAREAOUTPUT_H

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
};

#endif // CBAREAOUTPUT_H
