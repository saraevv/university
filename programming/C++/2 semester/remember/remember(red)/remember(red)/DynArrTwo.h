#pragma once
#include "DynArr.h"
#include <initializer_list>
using namespace std;

class DynArrTwo: public DynArr
{
public:
	DynArrTwo();
	DynArrTwo(initializer_list<int> l1, initializer_list<int> l2) : sn(l2.size()), DynArr(l1)
	{
		sarr = new int[sn];
		int k = 0;
		for (auto it = l2.begin(); it != l2.end(); ++it)
		{
			sarr[k++] = *it;
		}
	}
	DynArrTwo(DynArrTwo const &A2);
	DynArrTwo(DynArr const &A2);
	DynArrTwo& operator = (DynArrTwo const &A2);
	DynArrTwo(DynArrTwo &&A2);
	DynArrTwo& operator = (DynArrTwo &&A2);
	~DynArrTwo();
	DynArrTwo & operator+=(DynArr const & A2);
	int GetSN()const override { return sn; }
	int* GetSArr()const override { return sarr; }
	void SetSN(int n)override { sn = n; }
	void SetSArr(int* arr)override { sarr = arr; }
	void Print()const override;
	int Type()const override { return 2; }
protected:
	int sn;
	int* sarr;
};

