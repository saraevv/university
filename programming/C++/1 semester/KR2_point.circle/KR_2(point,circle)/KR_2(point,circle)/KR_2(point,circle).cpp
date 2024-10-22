#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;
class Point;
class PointProxy
{
public:
	PointProxy(Point *p);
	~PointProxy();
	operator Point const & () const;
	operator Point  & () const;
	friend ostream& operator << (ostream &os, PointProxy const & p);
	PointProxy operator + (Point const & t)const;
	Point *pP;
};

class Point
{
public:
	Point(double tx = 0, double ty = 0) :x(tx), y(ty) {}
	virtual ~Point() {}
	const double X()const  { return x; }
	const double Y()const  { return y; }
	virtual  Point* Clone()const { return new Point(x, y); }
	virtual const double R()const  { return 0; }
	void SetP(double tx, double ty)
	{
		x = tx;
		y = ty;
	}
	virtual void SetR(double tr) { }
	virtual Point& operator +=(Point const &p2)
	{
		x = (x + p2.X()) / 2;
		y = (y + p2.Y()) / 2;
		return *this;
	}
	friend ostream & operator << (ostream &os, Point &p)
	{
		os << "x=" << p.x << "; y=" << p.y;
		if (p.R())
			os << "; radius=" << p.R();
		os << endl;
		return os;
	}
	virtual PointProxy operator + (Point const & p2)const
	{
		Point* pt = p2.Clone();
		pt->SetP((X() + p2.X()) / 2, (Y() + p2.Y()) / 2);
		return PointProxy(pt);
	}
protected:
	double x;
	double y;
};

class Circle:public Point
{
public:
	Circle(double tradius, double tx, double ty) :radius(tradius), Point(tx, ty) {}
	const double R()const { return radius; }
	Point* Clone()const override { return new Circle(x, y, radius); }
	void SetR(double tr)override { radius = tr; }
	Circle& operator +=(Point const &p2)override
	{
		double tx = (x + p2.X()) / 2;
		double ty = (y + p2.Y()) / 2;
		if (sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y()))+p2.R()>radius)
		{
			radius = sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R();
			x = tx;
			y = ty;
		}
		return *this;
	}
	PointProxy operator + (Point const & p2)const override
	{
		Point* pt = Clone();
		if (sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R() > radius)
		{
			pt->SetP((x + p2.X()) / 2, (y + p2.Y()) / 2);
			pt->SetR(sqrt((x - p2.X())*(x - p2.X()) + (y - p2.Y())*(y - p2.Y())) + p2.R());
		}
		return PointProxy(pt);
	}
protected:
	double radius;
};

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

int main()
{
	Point p1(5, 5),p2(7,4);
	Circle c1(10, 3, 3),c2(3,4,5);
	
	cout << p1 + p2 << endl;
	cout << p1 + c1 << endl;
	cout << c1 + c2 << endl;
	cout << c1 + p1 << endl;

}

