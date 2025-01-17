#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	class Node
	{
	public:
		Node(int tvalue) : value(tvalue), next(nullptr) {}
		int value;
		Node *next;
	};

	class List
	{
	public:
		List() : first(nullptr), last(&first) {}

		void PushBack(int x)
		{
			Node *p = new Node(x);
			*last = p;
			last = &p->next;
		}

		void Print()
		{
			Node *p = first;
			while (p)
			{
				cout << p->value << " ";
				p = p->next;
			}
			
		}

		void Association(List L1, List L2)
		{
			Node *ptr1 = L1.first;
			Node *ptr2 = L2.first;
			while (ptr1 && ptr2)
			{
				PushBack(ptr1->value);
				ptr1 = ptr1->next;
				PushBack(ptr2->value);
				ptr2 = ptr2->next;
			}
			if (ptr1)
			{
				while (ptr1)
				{
					PushBack(ptr1->value);
					ptr1 = ptr1->next;
				}
			}
		
			if (ptr2)
			{
				while (ptr2)
				{
					PushBack(ptr2->value);
					ptr2 = ptr2->next;
				}
			}
			
		}

		Node *first;
		Node **last;
	};

	List L1, L2, L3;
	int x, n1, n2;
	cout << "Введите количество элементов в первом списке: ";
	cin >> n1;
	cout << "Введите количество элементов во втором списке: ";
	cin >> n2;
	cout << "Введите элементы первого списка: ";
	for (int i = 0; i < n1; ++i)
	{
		cin >> x;
		L1.PushBack(x);
	}
	cout << "Введите элементы второго списка: ";
	for (int i = 0; i < n2; ++i)
	{
		cin >> x;
		L2.PushBack(x);
	}
	
	L3.Association(L1, L2);
	L3.Print();
	system("pause");
	return 0;
}

