#include "Rat.h"
#include <iostream>
using namespace std;

int main()
{
	Rat r1, r2;
	cin >> r1 >> r2;
	cout << r1 << " " << r2 << endl;
	Rat r = r1 + r2;
	cout << r << endl;
	r = r1 - r2;
	cout << r << endl;
	r = r1 * r2;
	cout << r << endl;
	r = r1 / r2;
	cout << r << endl;
	cout << (r1 != r2);
	return 0;
}