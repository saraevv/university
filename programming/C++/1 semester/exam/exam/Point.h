#pragma once
#include <iostream>
using namespace std;
class Point
{
public:
	Point() :coord(0) {}
	Point(double x) :coord(x) {}
	virtual ~Point() {}
	virtual int Type();
	friend ostream& operator << (ostream& os, Point& P);
	double coord;
};

class Left :public Point
{
public:
	Left(double x) :Point(x) {}
	int Type()override;
};

class Right :public Point
{
public:
	Right(double x) :Point(x) {}
	int Type()override;
};
