#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	const int n = 15;
	int a[n];
	cout << "Enter " << n << "elements: ";
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	int b;
	int c;
	int x = a[0];
	for (int k = 0; k < n; ++k) {
		b = a[k];
		if (x > b) {
			x = b;
			c = k;
		}
	}
	return 0;
}

