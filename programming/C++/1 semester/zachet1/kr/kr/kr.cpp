#include "pch.h"
#include <iostream>
#include "Point.h"
using namespace std;

int main()
{
	Point p1(5, 3), p2(3, 4);
	Circle c1(5, 4, 3), c2(1, 1, 1);
	p1 += p2;
	p2 += c1;
	c1 += c2;
	c2 += p1;
	
	cout << p1 << p2 << c1 << c2;

	Point **p = new Point*[4]
	{ 
	new Point(5, 5),
	new Circle(1, 1, 1),
	new Circle(2, 2, 2),
	new Circle (3, 3, 3)
	};
	int np=0, nc=0;
	for (int i = 0; i < 4; ++i)
	{
		if (p[i]->Type() == 1)
			++np;
		else nc++;
	}
	cout << np << " " << nc << endl;
	return 0;
}

