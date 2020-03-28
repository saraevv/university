#pragma once
#include <iostream>
#include <initializer_list>
#include <algorithm>
using namespace std;

class KynArrTwo;

class KDynArr
{
public:
	KDynArr() :farr(nullptr), fn(0) {}
	KDynArr(initializer_list<int> l) : fn(l.size())
	{
		farr = new int[fn];
		int k = 0;
		for (auto it = l.begin(); it != l.end(); ++it)
		{
			farr[k++] = *it;
		}
	}
	KDynArr(const KDynArr& A2)
	{
		int *ptr;
		A2.GetFArr(fn, ptr);
		farr = new int[fn];
		for (int i = 0; i < fn; ++i)
			farr[i] = ptr[i];
	}
	KDynArr(KDynArr&&arr)=default;
	KDynArr& operator = (KDynArr&& A2)=default;
	virtual ~KDynArr() { }
	int Type() { return 1; }
	virtual void Print()const;
	int GetFN()const { return fn; }
	virtual int GetSN()const { return 0; }
	void GetFArr(int &n, int*&ptr)const { n = fn; ptr = farr; }
	int* GetFPtr()const { return farr; }
	virtual int* GetSPtr()const { return nullptr; }
	virtual void GetSArr(int& n, int*& ptr)const { n = 0; ptr = nullptr; }
	virtual KDynArr& operator = (const KDynArr& A2);
	virtual KDynArr& operator += (const KDynArr& A2);
protected:
	int * farr;
	int fn;
};

class KDynArrTwo : public KDynArr
{
public:
	KDynArrTwo() :sarr(nullptr), sn(0), KDynArr() {}
	KDynArrTwo(initializer_list<int> l1, initializer_list<int> l2) : sn(l2.size()), KDynArr(l1)
	{
		sarr = new int[sn];
		int k = 0;
		for (auto it = l2.begin(); it != l2.end(); ++it)
		{
			sarr[k++] = *it;
		}
	}
	KDynArrTwo(const KDynArrTwo& A2)
	{
		int *ptr;
		A2.GetFArr(fn, ptr);
		farr = new int[fn];
		for (int i = 0; i < fn; ++i)
			farr[i] = ptr[i];
		A2.GetSArr(sn, ptr);
		sarr = new int[sn];
		for (int i = 0; i < fn; ++i)
			sarr[i] = ptr[i];
	}
	KDynArrTwo(KDynArrTwo&&arr) = default;
	KDynArrTwo& operator = (KDynArrTwo&& A2) = default;
	void Print()const override;
	int GetSN()const override { return sn; }
	void GetSArr(int& n, int*& ptr)const override { n = sn; ptr = sarr; }
	int* GetSPtr()const override { return sarr; }
	KDynArr& operator = (const KDynArr& A2)override;
	KDynArrTwo& operator +=(const KDynArr& A2)override;
protected:
	int * sarr;
	int sn;
};

void KDynArr::Print()const
{
	for (int i = 0; i < fn; ++i)
		cout << farr[i] << " ";
	cout << endl;
}

void KDynArrTwo::Print()const 
{
	for (int i = 0; i < fn; ++i)
		cout << farr[i] << " ";
	cout << endl;
	for (int i = 0; i < sn; ++i)
		cout << sarr[i] << " ";
	cout << endl;
}

KDynArr & KDynArr::operator=(const KDynArr& A2)
{

	if (GetFPtr() == A2.GetFPtr());
	else
	{
		delete[]farr;
		int *ptr;
		A2.GetFArr(fn, ptr);
		farr = new int[fn];
		for (int i = 0; i < fn; ++i)
			farr[i] = ptr[i];
	}
	return *this;
}

KDynArr & KDynArrTwo::operator=(const KDynArr& A2)
{
	if (GetFPtr() == A2.GetFPtr() && GetSPtr() == A2.GetSPtr());
	else
	{
		delete[]farr;
		int *ptr;
		A2.GetFArr(fn, ptr);
		farr = new int[fn];
		for (int i = 0; i < fn; ++i)
			farr[i] = ptr[i];
		delete[]sarr;
		A2.GetSArr(sn, ptr);
		sarr = new int[sn];
		for (int i = 0; i < sn; ++i)
			sarr[i] = ptr[i];
	}
	return *this;
}

KDynArr & KDynArr::operator+=(const KDynArr & A2)
{
	int * ptr, n;
	A2.GetFArr(n, ptr);
	int *tm = new int[max(n,fn)];
	int i = 0;
	for (i; i < min(n, fn); ++i)
		tm[i] = farr[i] + ptr[i];
	if (n > fn)
		for (i; i < n; ++i)
			tm[i] = ptr[i];
	else
		for (i; i < fn; ++i)
			tm[i] = farr[i];
	delete[]farr;
	farr = tm;
	fn = max(fn, n);
	return *this;
}

KDynArrTwo & KDynArrTwo::operator+=(const KDynArr & A2)
{
	int * ptr, n;
	A2.GetFArr(n, ptr);
	int *tm = new int[max(n, fn)];
	int i = 0;
	for (i; i < min(n, fn); ++i)
		tm[i] = farr[i] + ptr[i];
	if (n > fn)
		for (i; i < n; ++i)
			tm[i] = ptr[i];
	else
		for (i; i < fn; ++i)
			tm[i] = farr[i];
	delete[]farr;
	farr = tm;
	fn = max(n, fn);
	A2.GetSArr(n, ptr);
	tm = new int[max(n, sn)];
	i = 0;
	for (i; i < min(n, sn); ++i)
		tm[i] = sarr[i] + ptr[i];
	if (n > sn)
		for (i; i < n; ++i)
			tm[i] = ptr[i];
	else
		for (i; i < sn; ++i)
			tm[i] = sarr[i];
	delete[]sarr;
	sarr = tm;
	sn = max(n, sn);
	return *this;
}