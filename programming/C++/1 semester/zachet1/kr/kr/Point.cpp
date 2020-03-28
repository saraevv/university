#include "pch.h"
#include "Point.h"
#include <iostream>
using namespace std;


Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(double tx, double ty)
{
	x = tx;
	y = ty;
}

double Point::X()
{
	return x;
}

double Point::Y()
{
	return y;
}

double Point::R()
{
	return 0.0;
}

int Point::Type()
{
	return 1;
}

Point & Point::operator+=(Point & p2)
{
	x += p2.x;
	y += p2.y;
	return *this;
}


Circle::Circle():Point()
{
	radius = 0;
}

Circle::Circle(double tradius, double tx, double ty):Point(tx,ty)
{
	radius = tradius;
}

double Circle::R()
{
	return radius;
}

int Circle::Type()
{
	return 2;
}

Point & Circle::operator+=(Point & p2)
{
	x += p2.X();
	y += p2.Y();
	radius += p2.R();
	return *this;
}

ostream & operator<<(ostream&os, Point & p)
{
	os << p.X() << " " << p.Y() << " ";
	if (p.R())
		os << p.R() << endl;
	return os;
}
