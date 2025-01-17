#include "pch.h"
#include <iostream>
#include "Matrix.h"
#include <windows.h>
using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	cout << "Матрица M1:" << endl;
	Matrix M1;
	cin >> M1;
	cout << "Матрица M2:" << endl;
	Matrix M2;
	cin >> M2;
	Matrix M3;


	// ()
	cout << "Введите i,j: ";
	int i, j;
	cin >> i >> j;
	cout << "M1[i][j]: " << M1(i, j);

	// Cols
	cout << "Количество колонок в M1: " << M1.Cols() << endl;

	// Rows
	cout << "Количество строк в M1: " << M1.Rows() << endl;

	//Операторы

	// ==
	cout << "M1==M2:";
	bool tr = M1 == M2;
	cout << tr << endl;

	// !=
	cout << "M1!=M2:";
	tr = M1 != M2;
	cout << tr << endl;

	// =
	cout << "M3=M1" << endl << "M3=" << endl;
	M3 = M1;
	cout << M3;

	// +
	cout << "M3=M1+M2" << endl << "M3=" << endl;
	M3 = M1+M2;
	cout << M3;

	// +=
	cout << "M1+=M2" << endl << "M1=" << endl;
	M3 = M1;
	M3 += M2;
	cout << M3;

	// -
	cout << "M3=M1-M2" << endl << "M3=" << endl;
	M3 = M1 - M2;
	cout << M3;

	// -=
	cout << "M1-=M2" << endl << "M1=" << endl;
	M3 = M1;
	M3 -= M2;
	cout << M3;

	// *
	cout << "M3=M1*M2" << endl << "M3=" << endl;
	M3 = M1 * M2;
	cout << M3;

	// *=
	cout << "M1*=M2" << endl << "M1=" << endl;
	M3 = M1;
	M3 *= M2;
	cout << M3;
	

	return 0;
}
