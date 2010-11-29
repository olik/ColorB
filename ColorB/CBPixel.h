/*
 * Single pixel
*/
#ifndef CBPIXEL_H
#define CBPIXEL_H

class CBPixel
{
public:
    CBPixel()
    {
	x = 0;
	y = 0;
    }
    CBPixel(const int _x, const int _y)
    {
	x = _x;
	y = _y;
    }
    bool operator == (const CBPixel & SS) const
    {
	return ( (SS.GetX() == this->GetX()) && (SS.GetY() == this->GetY()) );
    }

    // x
private:
    int x;
public:
    void SetX(const int _x) { x = _x; }
    int GetX() const { return x; }

    // y
private:
    int y;
public:
    void SetY(const int _y) { y = _y; }
    int GetY() const { return y; }
};

#endif // CBPIXEL_H
