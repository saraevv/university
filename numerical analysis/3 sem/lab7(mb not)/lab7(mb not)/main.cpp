#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

//Размерность матрицы
int n = 12;

//Нахождение случайного числа
int Rand(int L, int R)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(L, R);

    return dis(gen);
}

//Вывод матрицы
void PrintMatrix(float** A)
{
    cout << "A:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
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
        cout << fixed << setprecision(15) << setw(20) << x[i] << " ";
    cout << endl
         << endl;
}

//Умножение матрицы на столбец
void Multiplication(float** A, float* x, float* ans)
{
    float s;

    for (int i = 0; i < n; ++i) {
        s = 0;
        for (int j = 0; j < n; ++j) {
            s += A[i][j] * x[j];
        }
        ans[i] = s;
    }
}

pair<float,int> norm(float* v) {
    float ans = fabs(v[0]);
    int num = 0;
    for (int i = 1; i < n; ++i) {
        if (fabs(v[i]) > ans) {
            ans = fabs(v[i]);
            num = i;
		}
	}
    return pair<float,int>(ans,num);
}

int sign(float x) {
    if (x > 0) {
        return 1;
    } else if (x < 0){
        return -1;
    } else {
        return 0;
	}
}

void SaveArray(float* v, float* x) {
	for (int i = 0; i < n; ++i) {
		x[i] = v[i];
	}
}

void Iterations1(float** A, int m) {
    float* u = new float[n];
    u[0] = 1;
    for (int i = 1; i < n; ++i) {
        u[i] = 0;
	}
    float* v = new float[n];
	float* um = new float[n];
	float* vm = new float[n];
	float* vm1 = new float[n];
	float* denom = new float[n];
	float* x = new float[n];
    pair<float,int> nv;

	for (int k = 1; true; ++k) {
		Multiplication(A, u, v);

		if (k >= 46) {
			cout << "u " << k << ":" << endl;
			PrintArray(u);
		}

		if (k == 50) {
			int num = norm(v).second;
			float l1 = v[num] * sign(u[num]);
			cout << "l1: " << l1 << endl;

			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "v - l1*u: " << endl;
			PrintArray(x);
			cout << "|| v - l1*u ||: " << norm(x).first << endl;

			for (int i = 0; i < n; ++i) {
				denom[i] = vm[i] - l1 * um[i];
			}
			int nd = norm(denom).second;
			float l2 = (vm1[nd] * norm(vm).first - l1 * vm[nd]) / denom[nd];
			cout << "l2: " << l2 << endl;

			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "x:" << endl;
			PrintArray(x);

			Multiplication(A, x, v);
			for (int i = 0; i < n; ++i) {
				v[i] -= l2 * x[i];
			}

			cout << "Ax-l2x: " << endl;
			PrintArray(v);
			cout << "|| Ax-l2 ||: " << norm(v).first << endl;

			delete[]v;
			delete[]u;
			delete[]um;
			delete[]vm;
			delete[]vm1;
			delete[]denom;
			delete[]x;
			break;
		}

		nv = norm(v);
		for (int i = 0; i < n; ++i) {
			u[i] = v[i] / nv.first;
		}

		if (k == m - 1) {
			SaveArray(u, um);
		}

		if (k == m) {
			SaveArray(v, vm);
		}

		if (k == m + 1) {
			SaveArray(v, vm1);
		}
	}
}

void Iterations2(float** A) {
	float* u = new float[n];
	u[0] = 1;
	for (int i = 1; i < n; ++i) {
		u[i] = 0;
	}
	float* v = new float[n];
	float* um = new float[n];
	float* vm = new float[n];
	float* vm1 = new float[n];
	float* denom = new float[n];
	float* x = new float[n];
	pair<float, int> nv;

	for (int k = 1; true; ++k) {
		Multiplication(A, u, v);

		if (k >= 46) {
			cout << "u " << k << ":" << endl;
			PrintArray(u);
		}

		if (k == 50) {
			int num = norm(v).second;
			float l1 = v[num] * sign(u[num]);
			cout << "l1: " << l1 << endl;

			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "v - l1*u: " << endl;
			PrintArray(x);
			cout << "|| v - l1*u ||: " << norm(x).first << endl;

			for (int i = 0; i < n; ++i) {
				denom[i] = vm[i] - l1 * um[i];
			}
			int nd = norm(denom).second;
			float l2 = (v[nd] * norm(vm).first - l1 * vm[nd]) / denom[nd];
			cout << "l2: " << l2 << endl;


			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "x:" << endl;
			PrintArray(x);

			Multiplication(A, x, v);
			for (int i = 0; i < n; ++i) {
				v[i] -= l2 * x[i];
			}

			cout << "Ax-l2x: " << endl;
			PrintArray(v);

			cout << "|| Ax-l2 ||: " << norm(v).first << endl;

			delete[]v;
			delete[]u;
			delete[]um;
			delete[]vm;
			delete[]vm1;
			delete[]denom;
			delete[]x;
			break;
		}

		nv = norm(v);
		for (int i = 0; i < n; ++i) {
			u[i] = v[i] / nv.first;
		}

		if (k == 48) {
			SaveArray(u, um);
		}

		if (k == 49) {
			SaveArray(v, vm);
		}
	}
}

void Iterations3(float** A) {
	float* u = new float[n];
	u[0] = 1;
	for (int i = 1; i < n; ++i) {
		u[i] = 0;
	}
	float* v = new float[n];
	float* um = new float[n];
	float* vm = new float[n];
	float* vm1 = new float[n];
	float* denom = new float[n];
	float* x = new float[n];
	pair<float, int> nv;

	for (int k = 1; true; ++k) {
		Multiplication(A, u, v);

		if (k >= 46) {
			cout << "u " << k << ":" << endl;
			PrintArray(u);
		}

		if (k == 50) {
			float num = 0, den = 0;
			for (int i = 0; i < n; ++i) {
				num += v[i] * u[i];
				den += u[i] * u[i];
			}
			float l1 = num/den;
			cout << "l1: " << l1 << endl;

			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "v - l1*u: " << endl;
			PrintArray(x);

			for (int i = 0; i < n; ++i) {
				denom[i] = vm[i] - l1 * um[i];
			}
			int nd = norm(denom).second;
			float l2 = (v[nd] * norm(vm).first - l1 * vm[nd]) / denom[nd];
			cout << "l2: " << l2 << endl;

			for (int i = 0; i < n; ++i) {
				x[i] = v[i] - l1 * u[i];
			}

			cout << "x:" << endl;
			PrintArray(x);

			Multiplication(A, x, v);
			for (int i = 0; i < n; ++i) {
				v[i] -= l2 * x[i];
			}

			cout << "Ax-l2x: " << endl;
			PrintArray(v);

			cout << "|| Ax-l2 ||: " << norm(v).first << endl;

			delete[]v;
			delete[]u;
			delete[]um;
			delete[]vm;
			delete[]vm1;
			delete[]denom;
			delete[]x;
			break;
		}

		nv = norm(v);
		for (int i = 0; i < n; ++i) {
			u[i] = v[i] / nv.first;
		}

		if (k == 48) {
			SaveArray(u, um);
		}

		if (k == 49) {
			SaveArray(v, vm);
		}
	}
}

int main()
{
    setlocale(LC_ALL, "rus");
    //k=0
    //Создание матрицы n*n
    float** A = new float*[n];
    float** save = new float*[n];
    for (int i = 0; i < n; ++i) {
        A[i] = new float[n];
        save[i] = new float[n];
    }
    //Инициализация
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j) {
                if (i > j)
                    A[i][j] = A[j][i];
                else
                    A[i][j] = Rand(-4, 0);
            }

    for (int i = 0; i < n; ++i) {
        float s = 0;
        for (int j = 0; j < n; ++j)
            if (i != j)
                s -= A[i][j];
        A[i][i] = s;
    }
    A[0][0]++;
    //Вывод матрицы
    PrintMatrix(A);

	Iterations1(A, 30);

	cout << "___________________________________" << endl;

	Iterations2(A);

	cout << "___________________________________" << endl;

	Iterations3(A);

}