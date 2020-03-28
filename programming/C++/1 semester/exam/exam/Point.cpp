#include "pch.h"
#include "Point.h"




int Point::Type()
{
	return 0;
}



ostream & operator<<(ostream & os, Point & P)
{
	os << P.Type()*P.coord << "; ";
	return os;
}

int Left::Type()
{
	return -1;
}

int Right::Type()
{
	return 1;
}
