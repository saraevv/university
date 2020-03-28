#include "List.h"

void List::pushBack(int x)
{
	Node* ptr = new Node(x);
	*last = ptr;
	last = &ptr->next;
}

void List::print()
{
	Node* ptr = first;
	while (ptr)
	{
		std::cout << ptr->val << " ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

void List::swapElements(int f, int s)
{
	std::swap((*this)[f],(*this)[s]);
}

int List::count()
{
	int i = 0;
	Node* ptr = first;
	while (ptr)
	{
		++i;
		ptr = ptr->next;
	}
	return i;
}

int& List::operator[](int x)
{
	Node* ptr = first;
	int i = 0;
	while (ptr)
	{
		if (i == x)
			return ptr -> val;
		ptr = ptr->next;
		++i;
	}
	throw std::exception("Out of memory!");
}

ListIterator List::begin()
{
	return ListIterator(this, 0);;
}

ListIterator List::end()
{
	return ListIterator(this, this->count());
}

int& ListIterator::operator*()
{
	if (!isDone())
		return (*l)[n];
	throw std::exception("Out of memory!");
}

void ListIterator::swapValues(ListIterator it)
{
	std::swap(*(*this), *it);
}
