#include <iostream>
using namespace std;

constexpr int Size(int n, int x)
{
	int s = 0, xi = 1;
	for (int i = 0; i < n; ++i)
	{
		xi *= x;
		s += xi;
	}
	return s;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int array[Size(4, 3)];
	cout << "Размер массива: " << sizeof(array) / sizeof(array[0]) << endl;
}

