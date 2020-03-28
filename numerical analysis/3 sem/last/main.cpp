#include <fstream>
#include <iomanip>
#include <random>
#include <fcntl.h>
#include <io.h>
#include <limits>
#include <set>
#include <algorithm>

#define NEWTON 1
#define BISECTION 2
#define MPI 3
using namespace std;

ofstream fout("output.txt");

//Размерность матрицы
int n = 4;

//Нахождение случайного числа
int Rand(int L, int R) {
    static random_device rd;
    static mt19937 gen(time(0));
    uniform_int_distribution<> dis(L, R);

    return dis(gen);
}

//Вывод матрицы
void PrintMatrix(float **A) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fout << fixed << setprecision(8) << setw(20) << A[i][j] << " ";
        }
        fout << endl;
    }

    fout << endl;
}

//Вывод многочлена
void PrintPolynomial(vector<float> v) {
    for (int i = 0; i < v.size() - 2; ++i) {
        fout << "( " << v[i] << " ) *x^" << v.size() - i - 1 << " + ";
    }
    fout << "( " << v[v.size() - 2] << " ) *x + ( " << v[v.size() - 1] << " );";
    fout << endl;
}

//Сохранение матрицы
void SaveMatrix(float **save, float **source) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            save[i][j] = source[i][j];
        }
    }
}

//Метод Данилевского
void Danilevsky(float **A, float ***Mi) {
    float **M = new float *[n];
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
                    } else {
                        M[j][k] = 0;
                    }
                }
            }
        }

        for (int j = 0; j < n; ++j) {
            if (j == i - 1) {
                M[i - 1][j] = 1 / A[i][i - 1];
            } else {
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
            } else {
                A[i][j] = 1;
            }
        }
        SaveMatrix(Mi[i], M);
        fout << "M" << i << ":" << endl;
        PrintMatrix(M);
    }
}

//Нахождение значения функции в точке x
float fValue(float x, vector<float> v) {
    float ans = 0;
    for (int i = 0; i < v.size(); ++i) {
        ans += v[i] * pow(x, v.size() - i - 1);
    }
    return ans;
}

//Нахождение границ
float Borders(vector<float> v) {
    float c = INT_MIN;
    for (int i = 1; i < v.size(); ++i) {
        if (c < fabs(v[i])) {
            c = fabs(v[i]);
        }
    }
    return 1 + c / fabs(v[0]);

}

//Метод Ньютона
float Newton(float x, vector<float> v) {
    vector<float> dv;
    for (int i = 0; i < v.size() - 1; ++i) {
        dv.push_back(v[i] * (v.size() - i - 1));
    }
    float x1, fx, dfx;
    for (int i = 0; i < 100; ++i) {
        fx = fValue(x, v);
        dfx = fValue(x, dv);
        x = x - (fx / dfx);
    }
    return x;
}

//Метод простых итераций
float Mpi(float x, vector<float> v, float l, float r) {
    vector<float> dv;
    for (int i = 0; i < v.size() - 1; ++i) {
        dv.push_back(v[i] * (v.size() - i - 1));
    }
    float ldv = fValue(l, dv), rdv = fValue(r, dv);
    float C = 0;
    if (ldv < 0 && rdv < 0) {
        C = -2 / min(ldv, rdv);
    } else {
        C = -2 / max(ldv, rdv);
    }
    float tx;
    for (int k = 0; k < 1000000; ++k) {
        tx = x + C * fValue(x, v);
        if (fabs(x - tx) < 0.000001f) {
            return tx;
        }
        x = tx;
    }
    return x;
}

//Метод биссекций
float Bisection(float l, float r, vector<float> v) {
    float x, fx;
    while (fabs(l - r) > 0.000001f) {
        x = (l + r) / 2;
        fx = fValue(x, v);
        if (fabs(fx) < 0.000001f) {
            return x;
        } else if (fValue(l, v) * fx < 0) {
            r = x;
        } else {
            l = x;
        }
    }
    return (l + r) / 2;
}

//Поиск корней по промежуткам
vector<float> EquationSolution(vector<float> v, vector<float> st_points, int type, bool print_intervals = false) {
    float border = Borders(v);
    set<pair<float, float>> intervals;
    for_each(st_points.begin(), st_points.end(), [&border, &intervals](float x) {
        if (fabs(x) < border) {
            if (intervals.empty()) {
                intervals.emplace(-border, x);
            } else {
                auto it = --intervals.end();
                intervals.emplace((*it).second, x);
            }
        }
    });
    auto it = --intervals.end();
    intervals.emplace((*it).second, border);
    if (print_intervals) {
        for_each(intervals.begin(), intervals.end(),
                 [](pair<float, float> x) { fout << "[ " << x.first << " ; " << x.second << " ]\t"; });
        fout << endl;
    }
    vector<float> ans;
    float xi = 0;
    for_each(intervals.begin(), intervals.end(), [&v, &ans, &type, &xi](pair<float, float> x) {
        if (fValue(x.first, v) * fValue(x.second, v) < 0) {
            if (type == NEWTON) { xi = Newton((x.first + x.second) / 2, v); }
            if (type == BISECTION) { xi = Bisection(x.first, x.second, v); }
            if (type == MPI) { xi = Mpi((x.first + x.second) / 2, v, x.first, x.second); }
            ans.push_back(xi);
        }
    });
    return ans;
}

int main() {
    //Создание и инициализация матрицы
    float **A = new float *[n];
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

    float ***Mi = new float **[n];
    for (int i = 0; i < n; ++i) {
        Mi[i] = new float *[n];
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

    vector<float> v{1.0f, -A[0][0], -A[0][1], -A[0][2], -A[0][3]};
    fout << "x: ";
    PrintPolynomial(v);

    float b = v[1] / 2;
    float c = v[2] / 6;
    float D = b * b - 4 * c;
    if (D <= 0) {
        fout << "!";
        return 0;
    }
    float x1 = (-b - sqrt(D)) / 2;
    float x2 = (-b + sqrt(D)) / 2;
    vector<float> dv_points = {x1, x2};
    vector<float> dv = {1.0f, v[1] * 3 / 4, v[2] / 2, v[3] / 4};

    fout << "x\': ";
    PrintPolynomial(dv);

    fout << "Intervals of monotony for x\': ";
    vector<float> v_points = EquationSolution(dv, dv_points, NEWTON, true);

    fout << "Solutions for x\': " << endl;
    fout << "Newton: " << endl;
    for_each(v_points.begin(), v_points.end(), [](float x) { fout << x << '\t'; });
    fout << endl;

    v_points = EquationSolution(dv, dv_points, MPI);
    fout << "MPI: " << endl;
    for_each(v_points.begin(), v_points.end(), [](float x) { fout << x << '\t'; });
    fout << endl;

    sort(v_points.begin(), v_points.end());

    fout << "Intervals of monotony for x: ";
    vector<float> ans = EquationSolution(v, v_points, BISECTION, true);
    fout << "Solutions for x: " << endl;
    fout << "Bisection: ";
    for_each(ans.begin(), ans.end(), [](float x) { fout << x << " ; "; });
    fout << endl;

    ans.clear();
    ans = EquationSolution(v, v_points, MPI);
    fout << "MPI: ";
    for_each(ans.begin(), ans.end(), [](float x) { fout << x << " ; "; });
    fout << endl;

    ans.clear();
    ans = EquationSolution(v, v_points, NEWTON);
    fout << "Newton: ";
    for_each(ans.begin(), ans.end(), [](float x) { fout << x << " ; "; });
    fout << endl;

}