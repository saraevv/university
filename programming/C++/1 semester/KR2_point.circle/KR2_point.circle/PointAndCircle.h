#pragma once


#include <iostream>
#include <algorithm>
#include "pch.h"
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
	const double X()const { return x; }
	const double Y()const { return y; }
	virtual  Point* Clone()const { return new Point(x, y); }
	virtual const double R()const { return 0; }
	void SetP(double tx, double ty)
	{
		x = tx;
		y = ty;
	}
	virtual void SetR(double tr) { }
	virtual Point& operator +=(Point const &p2);
	friend ostream & operator << (ostream &os, Point &p);
	virtual PointProxy operator + (Point const & p2)const;
protected:
	double x;
	double y;
};

class Circle :public Point
{
public:
	Circle(double tradius, double tx, double ty) :radius(tradius), Point(tx, ty) {}
	const double R()const { return radius; }
	Point* Clone()const override { return new Circle(x, y, radius); }
	void SetR(double tr)override { radius = tr; }
	Circle& operator +=(Point const &p2)override;
	PointProxy operator + (Point const & p2)const override;
protected:
	double radius;
};

