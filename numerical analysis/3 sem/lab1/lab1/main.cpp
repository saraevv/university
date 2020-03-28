#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
using namespace std;

//Размерность матрицы
int n = 15;
//Номер в списке группы
int m = 13;
//Номер группы или 0
int k = 0;
//Нахождение случайного числа
int Rand(int L, int R) {
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dis(L, R);

	return dis(gen);
}

//Вывод матрицы
void PrintMatrix(float** A)
{
	cout << "A:" << endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << fixed << setprecision(3) << setw(10) << A[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

//Вывод столбца
void PrintArray(float* x)
{
	for (int i = 0; i < n; ++i)
		cout << fixed << setprecision(7) << setw(10) << x[i] << " ";
	cout << endl << endl;
}

//Умножение матрицы на столбец
void Multiplication(float** A, float* x, float* b)
{
	float s;

	for (int i = 0; i < n; ++i)
	{
		s = 0;
		for (int j = 0; j < n; ++j)
		{
			s += A[i][j] * x[j];
		}
		b[i] = s;
	}
}

//Нахождение решения СЛАУ без выбора ведущего элемента
void Gauss_1(float** A, float* b)
{
	float tm;
	for (int i = 0; i < n; ++i)
	{
		tm = A[i][i];
		b[i] /= tm;
		for (int j = i; j < n; ++j)
			A[i][j] /= tm;
		for (int j = i + 1; j < n; ++j)
		{
			tm = A[j][i];
			A[j][i] = 0;
			for (int k = i + 1; k < n; ++k)
				A[j][k] -= tm * A[i][k];
			b[j] -= tm * b[i];
		}
		if (!i)
		{
			cout << "Преобразованная матрица A после первого шага алгоритма:" << endl;
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					cout << fixed << setprecision(5) << setw(10) << A[i][j] << " ";
				}
				cout << setw(10) << "|" << b[i] << endl;
			}
			cout << endl;
		}
	}

	for (int i = n - 1; i > 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			tm = A[j][i];
			A[j][i] = 0;
			b[j] -= tm * b[i];
		}
	}

	cout << "Вектор приближенного значения x*:" << endl;
	PrintArray(b);
}

//Нахождение решение СЛАУ с выбором ведущего элемента по столбцу
void Gauss_2(float** A, float* b)
{
	float tm;
	float mx;
	for (int i = 0; i < n; ++i)
	{
		int ind = i;
		mx = A[i][i];
		for (int j = i + 1; j < n; ++j) {
			if (fabs(A[j][i]) > mx) {
				mx = fabs(A[j][i]);
				ind = j;
			}
		}
		swap(A[i], A[ind]);
		swap(b[i], b[ind]);
		tm = A[i][i];
		b[i] /= tm;
		for (int j = i; j < n; ++j)
			A[i][j] /= tm;
		for (int j = i + 1; j < n; ++j)
		{
			tm = A[j][i];
			A[j][i] = 0;
			for (int k = i + 1; k < n; ++k)
				A[j][k] -= tm * A[i][k];
			b[j] -= tm * b[i];
		}
		if (!i)
		{
			cout << "Преобразованная матрица A после первого шага алгоритма:" << endl;
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					cout << fixed << setprecision(5) << setw(10) << A[i][j] << " ";
				}
				cout << setw(10) << "|" << b[i] << endl;
			}
			cout << endl;
		}
	}

	for (int i = n - 1; i > 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			tm = A[j][i];
			A[j][i] = 0;
			b[j] -= tm * b[i];
		}
	}

	cout << "Вектор приближенного значения x*:" << endl;
	PrintArray(b);
}

//Нахождение относительной погрешности
float Fault(float* x, float* b)
{
	float* dx = new float[n];
	for (int i = 0; i < n; ++i)
		dx[i] = x[i] - b[i];
	float ndx = 0;
	for (int i = 0; i < n; ++i)
		ndx += dx[i] * dx[i];
	ndx = sqrt(ndx);

	float nx = 0;
	for (int i = 0; i < n; ++i)
		nx += x[i] * x[i];
	nx = sqrt(nx);
	cout << fixed << setprecision(7) << "Относительная погрешность: " << 100 * ndx / nx << "%" << endl << endl;
	return ndx / nx;
}

int main()
{
	setlocale(LC_ALL, "rus");
	//Задача №1
	//k=0
	//Создание матрицы n*n
	float** A = new float* [n];
	for (int i = 0; i < n; ++i)
	{
		A[i] = new float[n];
	}
	//Инициализация
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j)
				A[i][j] = Rand(-4, 0);

	for (int i = 0; i < n; ++i)
	{
		float s = 0;
		for (int j = 0; j < n; ++j)
			if (i != j)
				s -= A[i][j];
		A[i][i] = s;
	}
	A[0][0] += pow(10, -k);
	//Вывод матрицы
	PrintMatrix(A);

	//Создание и инициализация вектора x
	float* x = new float[n];

	cout << "x:" << endl;
	for (int i = 0; i < n; ++i)
		x[i] = m + i;
	PrintArray(x);

	//Создание и нахождение вектора b
	float* b = new float[n];
	Multiplication(A, x, b);
	cout << "b:" << endl;
	PrintArray(b);

	//Нахождение решения и вычисление погрешности
	Gauss_1(A, b);
	Fault(x, b);
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;

	//k=3
	k = 3;
	//Инициализация матрицы
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j)
				A[i][j] = Rand(-4, 0);

	for (int i = 0; i < n; ++i)
	{
		float s = 0;
		for (int j = 0; j < n; ++j)
			if (i != j)
				s -= A[i][j];
		A[i][i] = s;
	}
	A[0][0] += pow(10, -k);
	//Вывод матрицы
	PrintMatrix(A);

	//Создание и нахождение вектора b
	Multiplication(A, x, b);
	cout << "b:" << endl;
	PrintArray(b);

	//Нахождение решения и вычисление погрешности
	Gauss_1(A, b);
	Fault(x, b);
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;


	//Задача №2
	//Инициализация матрицы A
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
				A[i][j] = Rand(-100, 100);

	//Вывод матрицы
	PrintMatrix(A);

	//Нахождение вектора b
	Multiplication(A, x, b);
	cout << "b:" << endl;
	PrintArray(b);
	//Нахождение решения и вычисление погрешности
	Gauss_2(A, b);
	Fault(x, b);

	return 0;
}