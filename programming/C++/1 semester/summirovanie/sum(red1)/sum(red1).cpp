#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	double x, sum=0, d=1.0, p=0, m=1.0;
	cout << "Enter x, n (n>=0) " << endl;
	cin >> x >> n;
	for (int k = 1; k <= n; ++k) {
		m *= x;
		p += m;
		d = d * p * k / (n - k + 1);
		sum += d;
	}
	cout << "sum(" << x << ";" << n << ")=" << sum << endl;
	system("pause");
	return 0;
}