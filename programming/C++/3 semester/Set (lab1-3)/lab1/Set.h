#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include  <stdexcept>

class SetIterator;
class Visitor;
class VisitorSum;

class Set
{
public:
	Set();
	Set(const Set&);
	Set(Set&&);
	Set(std::initializer_list<int>);
	~Set();

	void Add(int);
	void Delete(int);
	int Count()const;
	int& GetItem(int)const;
	bool IsEmpty()const;
	int* GetArr()const;
	friend void SwapSet(Set&, Set&);
	bool operator == (Set& const);
	bool operator != (Set& const);
	void Clear();
	SetIterator CreateIterator();
	int Sum();

	friend std::ostream& operator << (std::ostream&, Set& const);
	Set& operator =(Set&const);
	Set& operator =(Set&&);
private:
	int* arr;
	int n;
};

class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual int& CurrentItem() const = 0;
};

class SetIterator : public Iterator
{
public:
	SetIterator(const Set* s);
	void First()override;
	void Next()override;
	bool IsDone()const override;
	int& CurrentItem()const override;
private:
	const Set* s;
	int current;
};

class Visitor
{
public:
	virtual void VisitInt(int&)=0;
protected:
	virtual ~Visitor() = default;
};

class VisitorSum :public Visitor
{
public:
	void VisitInt(int&)override;
	int GetSum();
private:
	int sum = 0;
};