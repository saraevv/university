#pragma once
#include <iostream>

class ListIterator;

class Node
{
public:
	int val;
	Node* next;
	Node(int val) :val(val), next(nullptr) {}
};

class List
{
	Node* first;
	Node** last;
public:
	List() :first(nullptr), last(&first) {}
	void pushBack(int x);
	void print();
	void swapElements(int, int);
	int count();
	Node* getFirst() { return first; }
	int& operator [](int);
	ListIterator begin();
	ListIterator end();

	template<class Compare>
	void sort(ListIterator first, ListIterator last, Compare comp);
};

class ListIterator
{
	List* l;
	int n;
public:
	ListIterator(List* l, int n) :l(l), n(n) {}
	List* getList() { return l; }
	int getN() { return n; }
	void first() { n = 0; }
	void operator ++() { ++n; };
	void operator --() { --n; };
	ListIterator operator -(const int& n) { return ListIterator(this->l,n-1); }
	bool isDone() { return n >= l->count(); };
	bool operator == (const ListIterator& l){ return this->n == l.n && this->l == l.l; }
	bool operator != (const ListIterator& l) { return !(*this==l); }
	int& operator * ();
	void swapValues(ListIterator it);
};

template<class Compare>
inline void List::sort(ListIterator first, ListIterator last, Compare comp)
{
	for (first; first != last; ++first)
	{
		ListIterator j(last.getList(), last.getN() - 1);
		ListIterator k(last.getList(), last.getN() - 2);
		for (j,k; j != first; --j, --k)
		{
			if (comp(*j, *k))
				j.swapValues(k);
		}
	}
}
