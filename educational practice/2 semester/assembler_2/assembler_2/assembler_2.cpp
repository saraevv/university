#include <iostream>
using namespace std;

extern "C" void Fasm(int*, int, int, int*);

void f(int * arr, int m, int n, int * ans)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			ans[j] += arr[i*n + j];
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	int *arr, n, m;
	cout << "Введите размерность матрицы: ";
	cin >> m >> n;
	arr = new int[m*n];
	cout << "Введите матрицу:" << endl;
	for (int i = 0; i < m*n; ++i)
		cin >> arr[i];
	int *ans = new int[n];
	for (int i = 0; i < n; ++i)
		ans[i] = 0;
	Fasm(arr, m, n, ans);
	cout << endl;
	for (int i = 0; i < n; ++i)
		cout << ans[i] << " ";
	return 0;
}