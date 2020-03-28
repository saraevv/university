#pragma once
#include <iostream>
using namespace std;
class Point
{
public:
	Point();
	Point(double tx, double ty);
	virtual ~Point() {}
	double X();
	double Y();
	virtual double R();
	virtual int Type();
	virtual Point & operator +=(Point &p2);
	friend ostream& operator << (ostream&os,Point &p);
protected:
	double x;
	double y;
};

class Circle :public Point
{
public:
	Circle();
	Circle(double tradius, double tx, double ty);
	double R()override;
	int Type()override;
	Point & operator +=(Point &p2)override;
protected:
	double radius;
};