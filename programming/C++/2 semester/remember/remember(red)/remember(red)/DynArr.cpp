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
	int* tm = A2.farr;
	for (int i = 0; i < fn; ++i)
		farr[i] = tm[i];
}

DynArr& DynArr::operator=(DynArr const &A2)
{
	DynArrTwo tm(A2);
	Swap(*this, tm);
	return *this;
}

DynArr::DynArr(DynArr &&A2)
{
	DynArr tm;
	Swap(tm, A2);
	Swap(*this, tm);
}

DynArr& DynArr::operator=(DynArr &&A2)
{
	if (farr != A2.farr)
	{
		DynArr tm;
		Swap(tm, A2);
		Swap(*this, tm);
	}
	return *this;
}


DynArr::~DynArr()
{
	fn = 0;
	delete[]farr;
}

void DynArr::Print()const
{
	for (int i = 0; i < fn; ++i)
		cout << farr[i] << " ";
	cout << endl;
}

DynArr & DynArr::operator+=(DynArr const &A2)
{
	int tn = A2.fn;
	int *tarr = new int[tn];
	int *ptr = A2.farr;
	int i = 0;
	for (i; i < min(fn, tn); ++i)
		tarr[i] = ptr[i] + farr[i];
	if (fn > tn)
		for (i; i < fn; ++i)
			tarr[i] = farr[i];
	else
		for (i; i < tn; ++i)
			tarr[i] = ptr[i];
	delete[]farr;
	farr = tarr;
	fn = tn;
	return *this;
}


void Swap(DynArr & A1, DynArr & A2)
{
	swap(A1.fn, A2.fn);
	swap(A1.farr, A2.farr);
	A2.SetSN(A1.GetSN());
	A2.SetSArr(A1.GetSArr());
	A1.SetSN(A2.GetSN());
	A1.SetSArr(A2.GetSArr());
}