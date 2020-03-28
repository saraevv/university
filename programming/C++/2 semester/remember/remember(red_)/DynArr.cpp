#include "DynArr.h"
#include "DynArrTwo.h"
#include <iostream>
#include <algorithm>
using namespace std;



DynArr::DynArr()
{
	farr = nullptr;
	fn = 0;
}

DynArr::DynArr(initializer_list<int> l)
{
	fn = l.size();
	farr = new int[fn];
	int k = 0;
	for (auto it = l.begin(); it != l.end(); ++it)
	{
		farr[k++] = *it;
	}
}

DynArr::DynArr(DynArr const &A2)
{
	fn = A2.fn;
	farr = new int[fn];
	for (int i = 0; i < fn; ++i)
		farr[i] = A2.farr[i];
}

DynArr & DynArr::operator=(DynArr const &A2)
{
	if (farr != A2.farr)
	{
		DynArrTwo tm(A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArr::DynArr(DynArr &&A2)
{
	farr = A2.farr;
	fn = A2.fn;
	/*DynArr tm;
	Swap(tm, A2);
	Swap(tm, *this);*/
	A2.farr = nullptr;
	A2.fn = 0;
}

DynArr & DynArr::operator=(DynArr &&A2)
{
	if (fn != A2.fn)
	{
		DynArr tm;
		Swap(tm, A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArr::~DynArr()
{
	fn = 0;
	delete[]farr;
}

void Swap(DynArr & A1, DynArr & A2)
{
	swap(A1.fn, A2.fn);
	swap(A1.farr, A2.farr);
	if (A1.Type() == 2 && A2.Type() == 2)
	{
		int tn = A1.GetSN();
		int* tarr = A1.GetSArr();
		A1.SetSArr(A2.GetSArr());
		A1.SetSN(A2.GetSN());
		A2.SetSN(tn);
		A2.SetSArr(tarr);
	}
}

void DynArr::Print()const
{
	for (int i = 0; i < fn; ++i)
		cout << farr[i] << " ";
	cout << endl;
}

DynArr & DynArr::operator+=(DynArr const &A2)
{
	int * tarr = new int[max(fn, A2.fn)];
	int i = 0;
	for (i; i < min(fn, A2.fn); ++i)
		tarr[i] = farr[i] + A2.farr[i];
	if (fn > A2.fn)
		for (i; i < fn; ++i)
			tarr[i] = farr[i];
	else if (fn < A2.fn)
		for (i; i < A2.fn; ++i)
			tarr[i] = A2.farr[i];
	else;
	farr = tarr;
	fn = max(fn, A2.fn);
	return *this;
}
