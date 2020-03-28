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
	int* ptr = A2.farr;
	for (int i = 0; i < fn; ++i)
		farr[i] = ptr[i];
	sn = A2.GetSN();
	sarr = new int[sn];
	ptr = A2.GetSArr();
	for (int i = 0; i < fn; ++i)
		sarr[i] = ptr[i];
}

DynArrTwo::DynArrTwo(DynArr const & A2)
{
	fn = A2.GetFN();
	farr = new int[fn];
	int* ptr = A2.GetFArr();
	for (int i = 0; i < fn; ++i)
		farr[i] = ptr[i];
	if (A2.Type() == 2)
	{
		sn = A2.GetSN();
		sarr = new int[sn];
		ptr = A2.GetSArr();
		for (int i = 0; i < sn; ++i)
			sarr[i] = ptr[i];
	}
	else
	{
		sarr = nullptr;
		sn = 0;
	}
}

DynArrTwo & DynArrTwo::operator=(DynArrTwo const & A2)
{
	if (GetFArr() != A2.GetFArr())
	{
		/*delete[]farr;
		fn = A2.GetFN();
		farr = new int[fn];
		int* ptr = A2.GetFArr();
		for (int i = 0; i < fn; ++i)
			farr[i] = ptr[i];
		ptr = A2.GetSArr();
		if (ptr)
		{
			delete[]sarr;
			sn = A2.GetSN();
			sarr = new int[sn];
			for (int i = 0; i < fn; ++i)
				sarr[i] = ptr[i];
		}*/
		DynArr tm(A2);
		Swap(*this, tm);
		return *this;
	}
	return *this;
}

DynArrTwo::DynArrTwo(DynArrTwo && A2)
{
	if (GetFArr() != A2.GetFArr())
	{
		DynArrTwo tm;
		Swap(tm, A2);
		Swap(*this, tm);
	}
}

DynArrTwo & DynArrTwo::operator=(DynArrTwo && A2)
{
	/*delete[]farr;
	delete[]sarr;
	fn = A2.GetFN();
	farr = A2.GetFArr();
	A2.SetFArr(nullptr);
	A2.SetFN(0);
	sn = A2.GetSN();
	sarr = A2.GetSArr();
	A2.SetSArr(nullptr);
	A2.SetSN(0);*/
	if (farr != A2.farr)
	{
		DynArr tm;
		Swap(tm, A2);
		Swap(*this, tm);
	}
	return *this;
}

DynArrTwo::~DynArrTwo()
{
	sn = 0;
	delete[]sarr;
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

DynArrTwo & DynArrTwo::operator+=(DynArr const & A2)
{
	int tn = A2.GetFN();
	int *ptr = new int[tn];
	int *arr = A2.GetFArr();
	int i = 0;
	for (i; i < min(tn, fn); ++i)
		ptr[i] = arr[i] + farr[i];
	if (tn > fn)
		for (i; i < tn; ++i)
			ptr[i] = arr[i];
	else
		for (i; i < fn; ++i)
			ptr[i] = farr[i];
	delete[]farr;
	farr = ptr;
	fn = tn;
	if (A2.Type() == 2)
	{
		tn = A2.GetSN();
		ptr = new int[tn];
		arr = A2.GetSArr();
		i = 0;
		for (i; i < min(tn, sn); ++i)
			ptr[i] = arr[i] + sarr[i];
		if (tn > sn)
			for (i; i < tn; ++i)
				ptr[i] = arr[i];
		else
			for (i; i < fn; ++i)
				ptr[i] = sarr[i];
		delete[]sarr;
		sarr = ptr;
		sn = tn;
	}
	return *this;
}
