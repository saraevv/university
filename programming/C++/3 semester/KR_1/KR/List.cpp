
#include "List.h"

void List::push_front(const int&r, const int&i)
{
	Complex* n_arr = new Complex[n + 1];
	n_arr[0] = Complex(r,i);
	for (int i = 0; i < n; ++i)
		n_arr[i + 1] = arr[i];
	++n;
	std::swap(arr, n_arr);
}

void List::push_back(const int&r, const int&i)
{
	Complex* n_arr = new Complex[n + 1];
	n_arr[n] = Complex(r,i);
	for (int i = 0; i < n; ++i)
		n_arr[i] = arr[i];
	++n;
	std::swap(arr, n_arr);
}

void List::pop_front()
{
	Complex* n_arr = new Complex[n - 1];
	for (int i = 1; i < n; ++i)
		n_arr[i - 1] = arr[i];
	--n;
	std::swap(arr, n_arr);
}

int& List::getItemReal(int i) const
{
	if (i < n)
		return arr[i].real;
	throw std::exception("Out of size!");
}
int& List::getItemImg(int i) const
{
	if (i < n)
		return arr[i].img;
	throw std::exception("Out of size!");
}

Complex& List::getItemComplex(int i) const
{
	if (i < n)
		return arr[i];
	throw std::exception("Out of size!");
}

ListIterator List::CreateIterator()
{
	return ListIterator(this, 0);
}

Complex* List::Min()
{
	VisitorMin v;
	for (auto it = this->CreateIterator(); !it.IsDone(); it.Next())
		it.CurrentItem().accept(v);
	return v.getMin();

}

Complex* List::Max()
{
	VisitorMax v;
	for (auto it = this->CreateIterator(); !it.IsDone(); it.Next())
		it.CurrentItem().accept(v);
	return v.getMax();

}

Complex& ListIterator::CurrentItem()
{
	if (!IsDone())
		return list->getItemComplex(n);
	throw std::exception("Out of size!");
}

void Complex::accept(Visitor& v)
{
	v.VisitComplex(*this);
}

void VisitorMin::VisitComplex(Complex&c)
{
	if (c.real < min)
	{
		min = c.real;
		current = &c;
	}
}

void VisitorMax::VisitComplex(Complex&c)
{
	if (c.img > max)
	{
		max = c.real;
		current = &c;
	}
}
