#include <fstream>
#include <iomanip>
#include <random>
#include <fcntl.h>
#include <io.h>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

ofstream fout("output.txt");

//Размерность матрицы
int n = 4;

//Нахождение случайного числа
int Rand(int L, int R) {
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dis(L, R);

	return dis(gen);
}

//Вывод матрицы
void PrintMatrix(float** A) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fout << fixed << setprecision(8) << setw(20) << A[i][j] << " ";
		}
		fout << endl;
	}

	fout << endl;
}

//Возврат знака
inline wchar_t sign(float x) {
	if (x >= 0)
		return L'+';
	return L'-';
}

//Сохранение матрицы
void SaveMatrix(float** save, float** source) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			save[i][j] = source[i][j];
		}
	}
}

//Метод Данилевского
void Danilevsky(float** A, float*** Mi) {
	float** M = new float* [n];
	for (int i = 0; i < n; ++i) {
		M[i] = new float[n];
	}
	for (int i = n - 1; i > 0; --i) {
		if (fabs(A[i][i - 1]) < 0.00000001f) {
			fout << "Bad matrix";
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					A[i][j] = Rand(-50, 50);
				}
			}
			Danilevsky(A, Mi);
			return;
		}
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				if (j != i - 1) {
					if (j == k) {
						M[j][k] = 1;
					}
					else {
						M[j][k] = 0;
					}
				}
			}
		}

		for (int j = 0; j < n; ++j) {
			if (j == i - 1) {
				M[i - 1][j] = 1 / A[i][i - 1];
			}
			else {
				M[i - 1][j] = -A[i][j] / A[i][i - 1];
			}

		}

		for (int j = 0; j < n; ++j) {
			if (j != i) {
				A[j][i - 1] /= A[i][i - 1];
			}
		}

		for (int j = 0; j < n; ++j) {
			if (j != i - 1) {
				for (int k = 0; k < n; ++k) {
					if (k != i) {
						A[k][j] -= A[k][i - 1] * A[i][j];
					}
				}
			}
		}

		for (int j = 0; j < n; ++j) {
			float s = 0;
			for (int k = 0; k < n; ++k) {
				if (k != i) {
					s += A[k][j] * A[i][k];
				}
			}
			A[i - 1][j] = s;
		}
		A[i - 1][i - 1] += A[i][i];

		for (int j = 0; j < n; ++j) {
			if (j != i - 1) {
				A[i][j] = 0;
			}
			else {
				A[i][j] = 1;
			}
		}
		SaveMatrix(Mi[i], M);
		fout << "M" << i << ":" << endl;
		PrintMatrix(M);
	}
}

//Нахождение значения функции в точке x
float fValue(float x, float* v, int l) {
	float ans = 0;
	for (int i = 0; i < l; ++i) {
		ans += v[i] * pow(x, l - i - 1);
	}
	return ans;
}

//Нахождение границ
float Borders(float* f, int l) {
	float b = INT_MIN, c = INT_MIN;
	//    for (int i = 0; i < l - 1; ++i) {
	//        if (b < fabs(f[i])) {
	//            b = fabs(f[i]);
	//        }
	//    }
	for (int i = 1; i < l; ++i) {
		if (c < fabs(f[i])) {
			c = fabs(f[i]);
		}
	}
	//return {fabs(f[l - 1]) / (fabs(f[l - 1]) + b), 1 + c / fabs(f[0])};
	return 1 + c / fabs(f[0]);

}

//Метод Ньютона
float Newton(float x, float* v) {
	float x1, fx, dfx;
	for (int i = 0; i < 100; ++i) {
		fx = v[0] * x * x * x + v[1] * x * x + v[2] * x + v[3];
		dfx = 3 * v[0] * x * x + 2 * v[1] * x + v[0];
		x = x - (fx / dfx);
	}
	return x;
}

//Метод бисекций
float Bisection(float x0, float x1, float* v, int l) {
	float x2, fx2;
	while ((x0 - x1) > 0.0000000001f) {
		x2 = (x0 + x1) / 2;
		fx2 = fValue(x2, v, 3);
		if (fabs(fx2) < 0.0000000001f) {
			return x2;
		}
		else if (fx2 * fValue(x0, v, l) < 0) {
			x1 = x2;
		}
		else {
			x0 = x2;
		}

	}
	return (x0 + x1) / 2;
}

float MPI(float x0, float* f, int l) {
	float* nf = new float[l];
	for (int i = 0; i < l; ++i) {
		if (i == l - 2) {
			nf[i] = 0;
		}
		else {
			nf[i] = -f[i] / f[l - 2];
		}
	}
	float tx;
	for (int k = 0; k < 1000; ++k) {
		tx = sqrt((-x0 * x0 * x0 - f[2] * x0 - f[3]) / f[1]);


		if (fabs(tx - x0) < 0.0000000001f) {
			return tx;
		}
		x0 = tx;
	}
	return x0;
}

void p1(float* v) {
	float b = v[1] / 2;
	float c = v[2] / 6;
	float D = b * b - 4 * c;
	if (D <= 0) {
		fout << "!";
		return;
	}
	float x1 = (-b - sqrt(D)) / 2;
	float x2 = (-b + sqrt(D)) / 2;

	float* f = new float[4];
	f[0] = 1.0f;
	f[1] = v[1] * 3 / 4;
	f[2] = v[2] / 2;
	f[3] = v[3] / 4;

	fout << endl << x1 << endl << x2 << endl;

	float border = Borders(f, 4);

	set<pair<float, float>> intervals;
	if (-border <= x1 && x2 <= border) {
		intervals.emplace(-border, x1);
		intervals.emplace(x1, x2);
		intervals.emplace(x2, border);
	}
	else if (fabs(x1) < border) {
		intervals.emplace(-border, x1);
		intervals.emplace(x1, border);
	}
	else {
		fout << "!!";
		exit(0);
	}
	for_each(intervals.begin(), intervals.end(),
		[](pair<float, float> x) { fout << x.first << " ; " << x.second << endl; });

	for_each(intervals.begin(), intervals.end(), [f](pair<float, float> x) {
		if (fValue(x.first, f, 4) * fValue(x.second, f, 4) < 0) {
			//fout << Bisection(x.first, x.second, f, 4) << endl;
			fout << "Newton: " << Newton((x.first + x.second) / 2, f) << endl;
			fout << "MPI: " << MPI((x.first + x.second) / 2, f, 4) << endl;
		}
		});

}

int main() {
	//Создание и инициализация матрицы
	float** A = new float* [n];
	for (int i = 0; i < n; ++i) {
		A[i] = new float[n];
		for (int j = 0; j < n; ++j) {
			A[i][j] = Rand(-5, 5);
		}
	}
	//Вывод матрицы
	fout << "A:" << endl;
	PrintMatrix(A);
	//Расчет главного значения матрицы
	float SpA = 0;
	for (int i = 0; i < n; ++i) {
		SpA += A[i][i];
	}

	float*** Mi = new float** [n];
	for (int i = 0; i < n; ++i) {
		Mi[i] = new float* [n];
		for (int j = 0; j < n; ++j) {
			Mi[i][j] = new float[n];
		}
	}

	//Метод Данилевского
	Danilevsky(A, Mi);

	//Вывод
	fout << "p1:" << " " << A[0][0] << endl;
	fout << "SpA:" << " " << SpA << endl;
	fout << "Characteristic polynomial: ";
	fout << "l^4 + (" << -A[0][0] << ") * l^3 + (" << -A[0][1] << ") * l^2 + (" << -A[0][2] << ") * l + (" << -A[0][3]
		<< ")" << endl;

	float* v = new float[n + 1];
	v[0] = 1;
	v[1] = -A[0][0];
	v[2] = -A[0][1];
	v[3] = -A[0][2];
	v[4] = -A[0][3];
	p1(v);
}