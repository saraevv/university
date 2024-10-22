#include "pch.h"
#include <iostream>
#include <windows.h>
#include "Point.h"
#include <fstream>
using namespace std;

double Sum(Point & P1, Point & P2)
{
	return P1.Type()*P1.coord + P2.Type()*P2.coord;
}

int main()
{
	ofstream of("output.txt");
	SetConsoleOutputCP(1251);
	Point **p = new Point*[10]
	{
		new Right(3.1),
		new Right(7.7),
		new Left(1.0),
		new Left(8.7),
		new Left(3.4),
		new Right(10.13),
		new Right(1.11),
		new Left(6.53),
		new Left(21.01),
		new Right(14.8)
	};
	for (int i = 0; i < 10; ++i)
		for (int j = 9; j > i; --j)
			if ((p[j - 1]->Type() == -1 && p[j]->Type() == -1 && p[j - 1]->coord < p[j]->coord) ||
				(p[j - 1]->Type() == 1 && p[j]->Type() == 1 && p[j - 1]->coord > p[j]->coord) ||
				(p[j - 1]->Type() > p[j]->Type()))
				swap(p[j - 1], p[j]);
	for (int i = 0; i < 10; ++i)
	{
		cout << *p[i];
	}
	cout << endl;

	int r;
	for (int i = 0; i < 10; ++i)
	{
		if (p[i]->Type() == 1)
		{
			r = i;
			break;
		}
	}
	double s;
	int num;
	for (int i = 0; i < r; ++i)
	{
		s = 10000;
		for (int j = r; j < 10; ++j)
		{
			if (abs(Sum(*p[i], *p[j])) < s)
			{
				s = abs(Sum(*p[i], *p[j]));
				num = j;
			}
		}
		cout << "Пара: ";
		cout << *p[i];
		cout << *p[num];
		cout << "с суммой " << s << endl;

		of << "Пара: ";
		of << p[i]->Type()*p[i]->coord << "; ";
		of << p[num]->Type()*p[num]->coord << "; ";
		of << "с суммой " << s << endl;
	}


}


