#include "pch.h"
#include "List.h"
#include <cmath>
void List::PushBack(int x)
{
	Node ** pp = last ? &last->next : &first;
	last = new Node(x, last, 0);
	*pp = last;
}

void List::Erase(Node * ptr)
{
	while (ptr)
	{
		Node * p = ptr;
		ptr = ptr->next;
		delete p;
	}
}

void List::Print()
{
	Node * p = first;
	while (p)
	{
		std::cout << p->info << " ";
		p = p->next;
	}
	std::cout << std::endl;
}

int List::Count()
{
	Node * p = first;
	int i = 0;
	while (p)
	{
		++i;
		p = p->next;
	}
	return i;
}

void List::DeleteEven()
{
	if (IsEmpty()) std::cout << "Список пуст!" << std::endl;
	else if (first == last && first->info % 2 == 0);
	else
	{
		Node *p = first;
		int n = Count();
		for (int i = 0; i < n; ++i)
		{
			if (abs(p->info )% 2 == 0)
			{
				Node *ptr = p;
				p = p->next;
				PushBack(ptr->info);
				Remove(ptr);
			}
			else
				p = p->next;
		}
	}
	
}

bool List::PopFront()
{
	bool b = false;
	Node ** pn = (first && first->next) ? &(first->next->prev) : &last;
	if (b = (first != 0))
	{
		first = first->next;
		delete *pn;
		*pn = 0;
	}
	return b;
}


bool List::PopBack()
{
	bool b = false;
	Node ** pp = (last && last->prev) ? &(last->prev->next) : &first;
	if (b = (last != 0))
	{
		last = last->prev;
		delete *pp;
		*pp = 0;
	}
	return b;
}

void List::Remove(Node *& p)
{
	if (p == first)
	{
		PopFront(); p = first;
	}
	else if (p == last)
	{
		PopBack(); p = 0;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		Node * q = p;
		p = p->next;
		delete q;
	}
	return;
}

void List::Invert()
{
	Node * p = first;
	while (p)
	{
		std::swap(p->prev, p->next);
		p = p->prev;
	}
	std::swap(first, last);
}

void List::MinofNegativ()
{
	if (IsEmpty())
		std::cout << "Список пуст!" << std::endl;
	else
	{
		int i = 0;
		Node *p = first;
		while (p)
		{
			if (p->info < i)
				i = p->info;
			p = p->next;
		}

		if (i == 0)
			std::cout << "В списке нет отрицательных элементов" << std::endl;
		else
			std::cout << "Минимальный отрицательный элемент: " << i << std::endl;
	}
}