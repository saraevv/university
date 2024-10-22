#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{	
	SetConsoleOutputCP(1251);
	class Queue
	{
	public:
		Queue(int size) :n(size), begin(0), end(0) { q = new int[n]; }
		
		void Push(int x)
		{
			q[end] = x;
			end = (end + 1)%n;
		}

		void Replace(int number)
		{
			begin = ++number;
			end = number;
		}

		void Print()
		{	
			int e = begin;
			do
			{
				cout << q[e] << " ";
				e = (e + 1) % n;
			} while (e != end);
		}

		int n, begin, end;
		int *q;
	};

	int size, number, w;
	cout << "Введите количество элементов в массиве: ";
	cin >> size;
	Queue Q(size);
	cout << "Введите элементы массива: ";
	for (int i = 0; i < size; ++i)
	{
		cin >> w;
		Q.Push(w);
	}
	cout << "Введите n: ";
	cin >> number;
	Q.Replace(number);
	Q.Print();
    return 0;
}

