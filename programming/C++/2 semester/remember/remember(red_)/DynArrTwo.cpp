#include "DynArrTwo.h"
#include <iostream>
#include <algorithm>
using namespace std;


DynArrTwo::DynArrTwo()
{
	sn = 0;
	sarr = nullptr;
}

DynArrTwo::DynArrTwo(DynArrTwo const & A2)
{
	fn = A2.fn;
	farr = new int[fn];
	for (int i = 0; i < fn; ++i)
		farr[i] = A2.farr[i];
	sn = A2.sn;
	sarr = new int[sn];
	for (int i = 0; i < sn; ++i)
		sarr[i] = A2.sarr[i];
}

DynArrTwo::DynArrTwo(DynArr const & A2)
{
	fn = A2.fn;
	farr = new int[fn];
	for (int i = 0; i < fn; ++i)
		farr[i] = A2.farr[i];
	if (A2.Type() == 2)
	{
		sn = A2.GetSN();
		int *tarr = A2.GetSArr();
		sarr = new int[sn];
		for (int i = 0; i < sn; ++i)
			sarr[i] = tarr[i];
	}
	else
	{
		sarr = nullptr;
		sn = 0;
	}
}

DynArrTwo & DynArrTwo::operator=(DynArrTwo const & A2)
{
	if (farr != A2.farr)
	{
		DynArrTwo tm(A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArrTwo & DynArrTwo::operator=(DynArr const & A2)
{
	if (farr != A2.farr)
	{
		DynArrTwo tm(A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArrTwo::DynArrTwo(DynArrTwo && A2)
{
	DynArrTwo tm;
	Swap(tm, A2);
	Swap(tm, *this);
}

DynArrTwo & DynArrTwo::operator=(DynArrTwo && A2)
{
	if (farr != A2.farr)
	{
		DynArrTwo tm;
		Swap(tm, A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArrTwo & DynArrTwo::operator=(DynArr && A2)
{
	if (farr != A2.farr)
	{
		DynArrTwo tm;
		Swap(tm, A2);
		Swap(tm, *this);
	}
	return *this;
}

DynArrTwo::~DynArrTwo()
{
	sn = 0;
	delete[]sarr;
}

DynArrTwo & DynArrTwo::operator+=(DynArr const & A2)
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
	if (A2.Type() == 2)
	{
		tarr = new int[max(sn, A2.GetSN())];
		i = 0;
		for (i; i < min(sn, A2.GetSN()); ++i)
			tarr[i] = sarr[i] + A2.GetSArr()[i];
		if (sn > A2.GetSN())
			for (i; i < sn; ++i)
				tarr[i] = sarr[i];
		else if (sn < A2.GetSN())
			for (i; i < A2.GetSN(); ++i)
				tarr[i] = A2.GetSArr()[i];
		else;
		sarr = tarr;
		sn = max(sn, A2.GetSN());
	}
	return *this;
}

void DynArrTwo::Print()const
{
	for (int i = 0; i < fn; ++i)
		cout << farr[i] << " ";
	cout << endl;
	for (int i = 0; i < sn; ++i)
		cout << sarr[i] << " ";
	cout << endl;
}