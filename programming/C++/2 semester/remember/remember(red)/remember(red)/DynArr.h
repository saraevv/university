#pragma once
#include <initializer_list>
using namespace std;
class DynArr
{
public:
	DynArr();
	DynArr(initializer_list <int> l);
	DynArr(DynArr const &);
	virtual DynArr& operator = (DynArr const &);
	DynArr(DynArr&&);
	virtual DynArr& operator = (DynArr&&);
	virtual~DynArr();
	int GetFN()const { return fn; }
	int* GetFArr()const { return farr; }
	void SetFN(int n) { fn = n; }
	void SetFArr(int* arr) { farr = arr; }
	virtual int GetSN()const { return 0; }
	virtual int* GetSArr()const { return nullptr; }
	virtual void SetSN(int n) { }
	virtual void SetSArr(int* arr) { }
	virtual int Type()const { return 1; }
	virtual void Print()const;
	friend void Swap(DynArr &A1, DynArr &A2);
	virtual DynArr& operator += (DynArr const&);
protected:
	int fn;
	int* farr;
};


