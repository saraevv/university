// Сараев В. М. 1 курс 3 группа
#include "pch.h"
#include <iostream>
#include "List.h"
#include <windows.h>
using namespace std;



int main()
{
	SetConsoleOutputCP(1251);
	List L;
	cout << "Введите количество элементов в списке: ";
	int n;
	cin >> n;
	if (n)
	{
		cout << "Введите элементы списка: " << endl;
		int x;
		for (int i = 0; i < n; ++i)
		{
			cin >> x;
			L.PushBack(x);
		}
}
	cout << "Список:" << endl;
	L.Print();
	cout << "Инвертирование элементов списка" << endl;
	L.Invert();
	L.Print();
	cout << "Удаление элементов с четными номерами" << endl;
	L.DeleteEven();
	L.Print();
	cout << "Нахождение минимального элемент среди отрицательных" << endl;
	L.MinofNegativ();
}

