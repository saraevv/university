#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>
using namespace std;

//Размерность матрицы
int n = 12;
//Номер в списке группы
int m = 13;
//Максимальное число итераций
int kmax = 1000;
//
float e = 0.0001;

//Нахождение погрешности
float Fault(float* x, float* b)
{
	float max = 0;
	for (int i = 0; i < n; ++i)
		if (fabs(x[i] - b[i]) > max)
			max = fabs(x[i] - b[i]);
	return max;
}

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

float* Jacobi(float** A, float* f)
{
	float** B = new float* [n];
	for (int i = 0; i < n; ++i)
		B[i] = new float[n];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
				B[i][j] = 0;
			else
				B[i][j] = -A[i][j];
		}
	}
	float* b = new float[n];
	float* ans = new float[n];
	for (int i = 0; i < n; ++i)
		ans[i] = b[i] = f[i];
	for (int k = 0; k < kmax; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			float s = f[i];
			for (int j = 0; j < n; ++j)
			{
				s += B[i][j] * b[j];
			}
			ans[i] = s / A[i][i];
		}
		if (Fault(ans, b) < e)
		{
			cout << "k = " << k << endl;
			delete[]b;
			for (int i = 0; i < n; ++i)
				delete[]B[i];
			return ans;
		}
		else
			for (int i = 0; i < n; ++i)
				b[i] = ans[i];
	}
	delete[]b;
	for (int i = 0; i < n; ++i)
		delete[]B[i];
	cout << "k = 1000" << endl;
	return ans;
}

float* Relaxation(float** A, float* f, float w)
{
	float** B = new float* [n];
	for (int i = 0; i < n; ++i)
		B[i] = new float[n];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
				B[i][j] = 0;
			else
				B[i][j] = -A[i][j];
		}
	}
	float* b = new float[n];
	float* ans = new float[n];
	for (int i = 0; i < n; ++i)
		ans[i] = b[i] = f[i];
	for (int k = 0; k < kmax; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			float s = f[i];
			for (int j = 0; j < n; ++j)
			{
					s += B[i][j] * ans[j];
			}
			ans[i] = ((s * w) / A[i][i]) + (1-w) * b[i];
		}
		if (Fault(ans, b) < e)
		{
			cout << "k = " << k << endl;
			delete[]b;
			for (int i = 0; i < n; ++i)
				delete[]B[i];
			return ans;
		}
		else
			for (int i = 0; i < n; ++i)
				b[i] = ans[i];
	}
	delete[]b;
	for (int i = 0; i < n; ++i)
		delete[]B[i];
	cout << "k = 1000" << endl;
	return ans;
}

int main()
{

	setlocale(LC_ALL, "rus");
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
		A[i][i] = 0;
		for (int j = 0; j < n; ++j)
			if (i != j)
				A[i][i] -= A[i][j];
	}
	++A[0][0];
	PrintMatrix(A);
	
	// Вектор x
	float* x = new float[n];
	for (int i = 0; i < n; ++i)
		x[i] = m + i;
	cout << "x:" << endl;
	PrintArray(x);

	//Вектор f
	float* f = new float[n];
	Multiplication(A, x, f);
	cout << "f:" << endl;
	PrintArray(f);

	cout << "Метод Якоби" << endl;
	float* ans = Jacobi(A, f);
	PrintArray(ans);

	cout << "Метод релаксации" << endl;
	cout << "w = 0.5" << endl;
	ans = Relaxation(A, f, 0.5);
	PrintArray(ans);

	cout << "w = 1" << endl;
	ans = Relaxation(A, f, 1);
	PrintArray(ans);

	cout << "w = 1.5" << endl;
	ans = Relaxation(A, f, 1.5);
	PrintArray(ans);
	
}