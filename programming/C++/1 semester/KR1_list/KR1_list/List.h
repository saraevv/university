#pragma once
#include <iostream>


class Node
{
public:
	Node() : info(0), prev(nullptr), next(nullptr) { }
	explicit Node(int tinfo) : info(tinfo), prev(nullptr), next(nullptr) { }
	Node(int tinfo, Node * tprev, Node * tnext): info(tinfo), prev(tprev), next(tnext) { }

	Node * prev;
	int info;
	Node * next;
};

class List
  {
public:
	List(): first(0), last(0) { }
	~List() { if (!IsEmpty()) Erase(first); }

	void PushBack(int x);
	bool IsEmpty() const { return first == 0; }
	void Print();
	int Count();
	void DeleteEven();
	void Invert();
	void MinofNegativ();
	bool PopFront();
	bool PopBack();
	void Remove(Node *& p);
   
private:
	void  Erase (Node * ptr);
	Node * first;
	Node * last; 
  };
