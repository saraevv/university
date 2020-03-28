#include "DynArr.h"
#include "DynArrTwo.h"
#include <iostream>
using namespace std;


DynArr GetA()
{
	DynArr a = { 1,2,3,4,5 };
	return a;
}

DynArrTwo GetB()
{
	DynArrTwo b = { {1,3,5,7},{2,4,6,8} };
	return b;
}

int main()
{
	/*DynArr a1 = { 2,4,3,23,17 };
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
	cout << "---------------------" << endl;*/

	////////////////////////////////////////////////////

	/*DynArr a1 = { 2, 4, 3, 23, 17 };
	DynArr a2(a1);
	DynArr a3;
	DynArr a4 = move(GetA());

	a1.Print();
	a2.Print();
	a3.Print();
	a4.Print();

	DynArrTwo b1({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo b2(b1);
	DynArrTwo b3;
	DynArrTwo b4 = move(GetB());

	b1.Print();
	b2.Print();
	b3.Print();*/

	////////////////////////////////////////////////////

	//DynArr *pa1 = new DynArr({ 2, 4, 3, 23, 17 });
	//DynArr *pa2 = new DynArr(*pa1);
	//DynArr *pa3 = new DynArr();
	////DynArr *pa4 = new DynArr(move(GetA()));

	//pa1->Print();
	//pa2->Print();
	//pa3->Print();
	////pa4->Print();

	//DynArrTwo *pb1 = new DynArrTwo({ 12, 32, 45 }, { 22, 33, 64 });
	//DynArrTwo *pb2 = new DynArrTwo(*pb1);
	//DynArrTwo *pb3 = new DynArrTwo();
	////DynArrTwo *pb4 = new DynArrTwo(move(GetB()));
	//DynArrTwo *pb5 = new DynArrTwo(*pa1);

	//pb1->Print();
	//pb2->Print();
	//pb3->Print();
	////pb4->Print();
	//pb5->Print();

	////////////////////////////////////////////////////

	/*DynArr a1 = { 2, 4, 3, 23, 17 };
	DynArr a2, a3;

	DynArrTwo b1({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo b2({ 21, 23, 54 }, { 29, 31, 46 });
	DynArrTwo b3({ 21, 23, 54 }, { 29, 31, 46 });

	a2 = a1;
	a3 = b1;
	b2 = a1;
	b3 = b1;

	a2.Print();
	a3.Print();
	b2.Print();
	b3.Print();*/

	////////////////////////////////////////////////////

	/*DynArr *pa1 = new DynArr({ 2, 4, 3, 23, 17 });
	DynArr *pa2 = new DynArr();
	DynArr *pa3 = new DynArr();

	DynArrTwo *pb1 = new DynArrTwo({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo *pb2 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });
	DynArrTwo *pb3 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });

	*pa2 = *pa1;
	*pa3 = *pb1;
	*pb2 = *pa1;
	*pb3 = *pb1;

	pa2->Print();
	pa3->Print();
	pb2->Print();
	pb3->Print();*/

	////////////////////////////////////////////////////

	/*DynArr a2, a3;

	DynArrTwo b2({ 21, 23, 54 }, { 29, 31, 46 });
	DynArrTwo b3({ 21, 23, 54 }, { 29, 31, 46 });

	a2 = move(GetA());
	a3 = move(GetB());
	b2 = move(GetA());
	b3 = move(GetB());

	a2.Print();
	a3.Print();
	b2.Print();
	b3.Print();*/

	////////////////////////////////////////////////////

	/*DynArr *pa2 = new DynArr();
	DynArr *pa3 = new DynArr();

	DynArrTwo *pb2 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });
	DynArrTwo *pb3 = new DynArrTwo({ 21, 23, 54 }, { 29, 31, 46 });

	*pa2 = move(GetA());
	*pa3 = move(GetB());
	*pb2 = move(GetA());
	*pb3 = move(GetB());

	pa2->Print();
	pa3->Print();
	pb2->Print();
	pb3->Print();*/

	////////////////////////////////////////////////////

	/*DynArr a1 = { 2, 4, 3, 23, 17 };
	DynArr a2(a1), a3(a1);

	DynArrTwo b1({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo b2(b1), b3(b1);

	a2 += a1;
	a3 += b1;
	b2 += a1;
	b3 += b1;

	a2.Print();
	a3.Print();
	b2.Print();
	b3.Print();*/

	////////////////////////////////////////////////////

	/*DynArr *pa1 = new DynArr({ 2, 4, 3, 23, 17 });
	DynArr *pa2 = new DynArr(*pa1);
	DynArr *pa3 = new DynArr(*pa1);

	DynArrTwo *pb1 = new DynArrTwo({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo *pb2 = new DynArrTwo(*pb1);
	DynArrTwo *pb3 = new DynArrTwo(*pb1);

	*pa2 += *pa1;
	*pa3 += *pb1;
	*pb2 += *pa1;
	*pb3 += *pb1;

	pa2->Print();
	pa3->Print();
	pb2->Print();
	pb3->Print();*/

	////////////////////////////////////////////////////

	//DynArrTwo b1({ 12, 32, 45 }, { 22, 33, 64 });
	//DynArrTwo b2;

	//b2 = *((DynArr*)&b1);
	////b2 += b2;

	//b1.Print();
	//b2.Print();

	////////////////////////////////////////////////////

	/*DynArrTwo *pb1 = new DynArrTwo({ 12, 32, 45 }, { 22, 33, 64 });
	DynArrTwo *pb2 = new DynArrTwo(*pb1);

	*pb2 = *pb1;

	pb1->Print();
	pb2->Print();*/

	DynArr a;
	a = GetA();
	return 0;
}