#include "List.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
T FSums(T a)
{
	return a;
}

template<typename T, typename...Args>
auto FSums(T a, Args...args)
{
	return [](auto a, auto b) { return a + b; }(a, FSums(args...));
}

template<typename T>
string ToString(char c, T a)
{
	return to_string(a);
}

template<typename T, typename...Args>
string ToString(char c, T a, Args...args)
{
	return [](char c, auto a, auto b)
	{
		return to_string(a) + c + b;
	}(c, a, ToString(c,args...));
}

int main()
{
	setlocale(LC_ALL, "rus");
	int n, x;
	List l;
	cout << "Введите количество элементов в списке: ";
	cin >> n;
	cout << "Введите элементы списка: " << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		l.pushBack(x);
	}
	// №1
	//1)
	for_each(l.begin(), l.end(), [](const int& a)
		{
			cout << a << " ";
		});
	cout << endl;
	//2)
	l.sort(l.begin(), l.end(), [](const int& a, const int& b) 
		{
			return abs(a) < abs(b);
		});
	l.print();
	//3)
	try
	{
		auto it = find_if(l.begin(), l.end(), [](const int& a)
			{
				return a % 2 == 0;
			});
		cout << *it << endl;
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	//4)
	x = 0;
	for_each(l.begin(), l.end(), [&x](const int& a)
		{
			if (a % 2 == 0)
				++x;
		});
	cout << x << endl;

	//5)
	for_each(l.begin(), l.end(), [](int& a)
		{
			if (a < 0)
			a = 0;
		});
	l.print();

	// №2
	auto ans = FSums(4, 8, 15.16, float(23), true, 'q', 42);
	cout << ans << endl;

	// №3
	string str = ToString(';', 1, 3.14, 2.22f, 'a', "hello");
	cout << str;
}