#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	double x, s = 1, d = 1;
	int n;
	cout << "Enter x, n";
	cin >> x >> n;
	for (int i = 1; i <= n; ++i)
	{
		d *= x / i;
		s += d;
		cout << "S=" << s << endl;
	}
	return 0;
}