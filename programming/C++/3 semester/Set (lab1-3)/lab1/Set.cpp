#include "Set.h"

Set::Set()
{
	arr = nullptr;
	n = 0;
}

Set::Set(const Set& s)
{
	n = s.n;
	arr = new int[n];
	for (int i = 0; i < n; ++i)
		arr[i] = s.arr[i];
}

Set::Set(Set&& s)
{
	arr = s.arr;
	n = s.n;
	s.arr = nullptr;
	s.n = 0;
}

Set::Set(std::initializer_list<int> list)
{
	arr = nullptr;
	n = 0;
	int i = 0;
	for (auto it = list.begin(); it != list.end(); ++i, ++it)
		Add(*it);
}

Set::~Set()
{
	delete[]arr;
	n = 0;
}

void Set::Add(int a)
{
	if (IsEmpty())
	{
		arr = new int[1];
		arr[0] = a;
		++n;
	}
	else
	{
		int i = 0;
		int* n_arr;
		while (true)
		{
			if ((i == n) || arr[i]>=a)
				break;
			++i;
		}
		if (i == n)
		{
			n_arr = new int[n+1];
			for (int j = 0; j < n; ++j)
				n_arr[j] = arr[j];
			n_arr[n] = a;
			std::swap(n_arr, arr);
			++n;
		}
		else if (arr[i] != a)
		{
			int* n_arr = new int[n+1];
			for (int j = 0, k = 0; j < n+1; ++j)
			{
				if (j == i)
					n_arr[j] = a;
				else
				{
					n_arr[j] = arr[k];
					++k;
				}
			}
			std::swap(n_arr, arr);
			++n;
		}
		
	}
}

void Set::Delete(int a)
{
	int* n_arr = new int[n - 1];
	for (int i = 0, j = 0; i < n; ++i)
	{
		if(arr[i]!=a)
		{
			n_arr[j] = arr[i];
			++j;
		}
	}
	--n;
	std::swap(arr, n_arr);
	delete[]n_arr;
}

int Set::Count()const
{
	return n;
}

int& Set::GetItem(int a)const
{
	return arr[a];
}

bool Set::IsEmpty()const
{
	return arr == nullptr;
}

int* Set::GetArr()const
{
	return arr;
}

bool Set::operator==(Set&const s)
{
	return arr == s.arr;
}

bool Set::operator!=(Set& const s)
{
	return !(*this==s);
}

void Set::Clear()
{
	delete[]arr;
	n = 0;
}

SetIterator Set::CreateIterator()
{
	return SetIterator(this);
}

int Set::Sum()
{
	VisitorSum s;
	for (auto it = CreateIterator(); !it.IsDone(); it.Next())
		s.VisitInt(it.CurrentItem());
	return s.GetSum();
}

Set& Set::operator=(Set& const s)
{
	Set tm(s);
	SwapSet(s, *this);
	return *this;
}
	
Set& Set::operator=(Set&&s)
{
	Set tm;
	SwapSet(s, tm);
	SwapSet(tm, *this);
	return *this;
}

void SwapSet(Set& s1, Set& s2)
{
	std::swap(s1.arr, s2.arr);
	std::swap(s1.n, s2.n);
}

std::ostream& operator<<(std::ostream& os, Set& const s)
{
	for (int i = 0; i < s.n; ++i)
		os << s.arr[i] << " ";
	os << std::endl;
	return os;
}

///

SetIterator::SetIterator(const Set* set)
{
	s = set;
	current = 0;
}

void SetIterator::First()
{
	current = 0;
}

void SetIterator::Next()
{
	++current;
}

bool SetIterator::IsDone() const
{
	return current >= s->Count();
}

int& SetIterator::CurrentItem() const
{
	if (IsDone())
		throw std::exception("Out of size!/n");
	return s->GetItem(current);
}

void VisitorSum::VisitInt(int&I)
{
	sum += I;
}

int VisitorSum::GetSum()
{
	return sum;
}
