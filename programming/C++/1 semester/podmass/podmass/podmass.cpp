#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;


int main()
{
	SetConsoleOutputCP(1251);
	int m, n, x;
	cout << "Введите количество элементов в массиве: ";
	cin >> n;
	int *arr = new int[n];
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		arr[i] = x;
	}
	cout << "Введите m: ";
	cin >> m;
	int l=0, r=n-1;
	for (int i = 0; i < (n / 2); ++i)
		swap(arr[l + i], arr[r - i]);
	l = n - m;
	r = n - 1;
	for (int i=0; i<(m/2); ++i)
		swap(arr[l + i], arr[r - i]);
	l = 0;
	r = n-m-1;
	for (int i = 0; i <((n-m)/2); ++i)
		swap(arr[l + i], arr[r - i]);
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << endl;
	system("pause");
    return 0;
}

