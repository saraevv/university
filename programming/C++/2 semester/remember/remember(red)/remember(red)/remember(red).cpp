#include "DynArr.h"
#include "DynArrTwo.h"
#include <iostream>
using namespace std;

int main()
{
	DynArr a1 = { 2,4,3,23,17 };
	a1.Print();
	cout << "---------------------" << endl;
	DynArr a2(a1);
	a2.Print();
	cout << "---------------------" << endl;
	DynArr a3;
	a3 = a1;
	a3.Print();
	cout << "---------------------" << endl;
	DynArrTwo b1({ 12,32,45 }, { 22,33,64 });
	b1.Print();
	cout << "---------------------" << endl;
	DynArrTwo b2, b3, b4(b1), b5(b1);
	b2 = b1;
	b2.Print();
	cout << "---------------------" << endl;
	b3 = a1;
	b3.Print();
	cout << "---------------------" << endl;
	a3 = b4;
	a3.Print();
	cout << "---------------------" << endl;
	DynArr * pb1 = new DynArrTwo({ 21,23,54 }, { 29,31,46 });
	pb1->Print();
	cout << "---------------------" << endl;
	b3 = *pb1;
	b3 += a1;
	b3.Print();
	cout << "---------------------" << endl;
	b4 += b5;
	b4.Print();
	cout << "---------------------" << endl;
	DynArr * pb2 = new DynArrTwo({ 21,23,54 }, { 29,31,46 });
	DynArr * pb3 = new DynArrTwo({ 21,23,54,99 }, { 29,31 });
	*pb3 = *pb2;
	pb3->Print();
	cout << "---------------------" << endl;
	*pb3 += *pb2;
	pb3->Print();
	cout << "---------------------" << endl;
	return 0;
}