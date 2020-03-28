#pragma once
#include <algorithm>
#include <limits.h>
class ListIterator;
class Visitor;
class VisitorMin;
class VisitiorMax;
struct Complex
{
	int real;
	int img;
	Complex() :real(0), img(0) {}
	Complex(const int& r, const int& i) :real(r), img(i) {}
	void accept(Visitor&);
};

class List
{
	Complex* arr;
	int n;
public:
	List() :arr(nullptr), n(0) {}
	void push_front(const int&, const int&);
	void push_back(const int&, const int&);
	void pop_front();
	bool IsEmpty()const { return n == 0; }
	int count()const { return n; }
	int& getItemReal(int)const;
	int& getItemImg(int)const;
	Complex& getItemComplex(int)const;
	ListIterator CreateIterator();
	Complex* Min();
	Complex* Max();
};

class Iterator
{
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Complex& CurrentItem() = 0;
};

class ListIterator :public Iterator
{
	List* list;
	int n;
public:
	ListIterator(List* list, int n) :list(list), n(n) {}
	void First()override { n = 0; }
	void Next()override { ++n; };
	bool IsDone()override { return n >= list->count(); };
	Complex& CurrentItem()override;
};

class Visitor
{
public:
	virtual void VisitComplex(Complex&) = 0;
};

class VisitorMin:public Visitor
{
	int min=INT_MAX;
	Complex* current;
public:
	void VisitComplex(Complex&)override;
	Complex* getMin() { return current; }
};

class VisitorMax :public Visitor
{
	int max = INT_MIN;
	Complex* current;
public:
	void VisitComplex(Complex&)override;
	Complex* getMax() { return current; }
};