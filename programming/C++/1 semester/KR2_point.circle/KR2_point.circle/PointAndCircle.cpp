#include "PointAndCircle.h"
#include "pch.h"

PointProxy::PointProxy(Point *p) :pP(p) {}

PointProxy::~PointProxy() { delete pP; }

PointProxy PointProxy::operator + (Point const & t)const
{
	return *pP + t;
}
PointProxy::operator Point const & () const { return *pP; }

PointProxy::operator Point  & () const { return *pP; }

ostream& operator << (ostream &os, PointProxy const & p)
{
	os << *(p.pP);
	return os;
}

Point& Point::operator +=(Point const &p2)
{
	x = (x + p2.X()) / 2;
	y = (y + p2.Y()) / 2;
	return *this;
}

ostream & operator << (ostream &os, Point &p)
{
	os << "x=" << p.x << "; y=" << p.y;
	if (p.R())
		os << "; radius=" << p.R();
	os << endl;
	return os;
}

PointProxy Point::operator + (Point const & p2)const
{
	Point* pt = p2.Clone();
	pt->SetP((X() + p2.X()) / 2, (Y() + p2.Y()) / 2);
	return PointProxy(pt);
}

Circle& Circle::operator +=(Point const &p2)
{
	double tx = (x + p2.X()) / 2;
	double ty = (y + p2.Y()) / 2;
	if (sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R() > radius)
	{
		radius = sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R();
		x = tx;
		y = ty;
	}
	return *this;
}

PointProxy Circle::operator + (Point const & p2)const 
{
	Point* pt = Clone();
	if (sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R() > radius)
	{
		pt->SetP((x + p2.X()) / 2, (y + p2.Y()) / 2);
		pt->SetR(sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R());
	}
	return PointProxy(pt);
}