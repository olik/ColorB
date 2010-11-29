#ifndef CBUTILS_H
#define CBUTILS_H

#include <QTime>

class CBUtils
{
private:
    CBUtils() { }

public:
    static int Random(const int x)
    {
	QTime midnight(0, 0, 0);
	qsrand(midnight.secsTo(QTime::currentTime()));
	return (qrand() % x);
    }
};

#endif // CBUTILS_H
