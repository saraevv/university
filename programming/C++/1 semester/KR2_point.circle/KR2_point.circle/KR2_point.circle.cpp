// Сараев В. М. 1 курс 3 группа
#include "pch.h"
#include <iostream>
#include "PointAndCircle.h"

int main()
{
	Point p1(5, 5), p2(7, 4);
	Circle c1(10, 3, 3), c2(3, 4, 5);

	cout << p1 + p2 << endl;
	cout << p1 + c1 << endl;
	cout << c1 + c2 << endl;
	cout << c1 + p1 << endl;

	return 0;
}