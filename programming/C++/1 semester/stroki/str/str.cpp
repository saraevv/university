#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{	
	int n;
	cout << "Enter number of elements" << endl;
	cin >> n;
	char* str = new char[n];
	cout << "Enter elements" << endl;
	for (int i = 0; i < n; ++i) cin >> str[i];
	cin >> str;
	int rep[256];
	for (int i = 0; i < 256; ++i) rep[i] = 0;
		for (int i = 0; i < n; ++i) {
			for (int k = i+1; k < n; ++k) {
				if (str[i] == str[k]) rep[str[i]] = 1;
			}
		}
	for (int i = 0; i < 256; ++i) if (rep[i]=1) cout << 1 ;
    return 0;
}

