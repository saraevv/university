#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	double x, z, x0, h;
	int n;
	cout << "Enter x0, h, n (n>0)";
	cin >> x0 >> h >> n;
	x = x0;
	for (int i = 0; i < n; ++i)
	{
		if (x >= 5) z = 2 * x + 3;
		else z = x * (x + 2);
		cout << "z=" << z << endl;
		x += h;
	}
	return 0;
}
