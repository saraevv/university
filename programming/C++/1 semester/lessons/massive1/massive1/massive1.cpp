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
	//for (int k = 0; k < n; ++k) 
	//s += a[k];
	int s = 0;
	for (auto x : a) s += x;
	cout << s;
	return 0;
}
