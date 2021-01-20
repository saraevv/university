#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include "mpi.h"

using namespace std;

const int N = 300;


void MatrixInput(vector<double> &matrix, ifstream fin = ifstream("input.txt")) {
    for (auto &elem:matrix) {
        fin >> elem;
    }
}

void MatrixOutput(vector<double> &matrix, ofstream fout = ofstream("output.txt")) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            fout << matrix[i * N + j] << ' ';
        }
        fout << '\n';
    }
}

int Rand(int L, int R) {
    static random_device rd;
    static mt19937_64 gen(time(nullptr));;
    uniform_int_distribution<> dis(L, R);
    return dis(gen);
}

void GenerateMatrix() {
    vector<double> matrix(N * N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i * N + j] = Rand(-100, 100);
        }
    }
    for (int i = 0; i < N; ++i) {
        int sum = 0;
        for (int j = 0; j < N; ++j) {
            if (j != i) {
                sum += matrix[i * N + j];
            }
        }
        matrix[i * N + i] = sum + 1;
    }
    MatrixOutput(matrix, ofstream("input.txt"));
}


int index(int i, int j, int size) {
    return i * size + j;
}

void LUDecomposition(vector<double> &submatrix, vector<int> &map, int size, int my_rank, int rank_count) {
    int first;
    MPI_Scan(&size, &first, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    first -= size;

    vector<double> current_row(N);

    for (int k = 0; k < N; ++k) {
        if (k >= first && k < first + size) {
            for (int i = 0; i < N; ++i) {
                current_row[i] = submatrix[index(k - first, i, N)];
            }
            for (int i = my_rank + 1; i < rank_count; ++i) {
                MPI_Send(current_row.data(), N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
        if (k >= first && k < first + size) {
            for (int p = k - first + 1; p < size; ++p) {
                submatrix[index(p, k, N)] /= submatrix[index(k - first, k, N)];
                for (int i = k + 1; i < N; ++i) {
                    submatrix[index(p, i, N)] -= submatrix[index(k - first, i, N)] * submatrix[index(p, k, N)];
                }
            }
        } else {
            if (map[k] > my_rank) continue;
            MPI_Recv(current_row.data(), N, MPI_DOUBLE, map[k], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int p = 0; p < size; ++p) {
                submatrix[index(p, k, N)] /= current_row[index(0, k, N)];
                for (int i = k + 1; i < N; ++i) {
                    submatrix[index(p, i, N)] -= submatrix[index(p, k, N)] * current_row[index(0, i, N)];
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    //GenerateMatrix();
    double start_time, end_time;
    int my_rank, rank_count;
    vector<double> matrix(N * N);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_count);

    if (my_rank == 0) {
        start_time = MPI_Wtime();
        cout << "Number of processes: " << rank_count << endl;
        MatrixInput(matrix);
    }

    int size = N / rank_count + (N % rank_count > my_rank ? 1 : 0);
    vector<double> submatrix(size * N);
    vector<int> displs(rank_count);
    vector<int> send_counts(rank_count);

    vector<int> map(N);

    int first;
    MPI_Scan(&size, &first, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    first -= size;
    for (int i = first; i < first + size; ++i) {
        map[i] = my_rank;
    }

    MPI_Allgather(&size, 1, MPI_INT, send_counts.data(), 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&first, 1, MPI_INT, displs.data(), 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgatherv(&map[first], size, MPI_INT, map.data(), send_counts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD);

    int current_size = N * size;
    MPI_Gather(&current_size, 1, MPI_INT, send_counts.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    displs[0] = 0;
    for (int i = 1; i < rank_count; ++i) {
        displs[i] = displs[i - 1] + send_counts[i - 1];
    }

    MPI_Scatterv(matrix.data(), send_counts.data(), displs.data(), MPI_DOUBLE, submatrix.data(), N * size, MPI_DOUBLE, 0,
                 MPI_COMM_WORLD);
    LUDecomposition(submatrix, map, size, my_rank, rank_count);

    vector<double> result(N * N);
    MPI_Gatherv(submatrix.data(), size * N, MPI_DOUBLE, result.data(), send_counts.data(), displs.data(), MPI_DOUBLE, 0,
                MPI_COMM_WORLD);
    if (my_rank == 0) {
        end_time = MPI_Wtime();
        cout << "Total time: " << end_time - start_time << endl;
        MatrixOutput(result);

        vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
        for (int i = 0; i < N; ++i) {
            L[i][i] = 1.0;
            for (int j = 0; j < N; ++j) {
                double cur = result[index(i, j, N)];
                if (j < i) {
                    L[i][j] = cur;
                } else {
                    U[i][j] = cur;
                }
            }
        }
        vector<double> mult(N * N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                double sum = 0.0;
                for (int k = 0; k < N; ++k) {
                    sum += L[i][k] * U[k][j];
                }
                mult[index(i, j, N)] = sum;
            }
        }
        bool tr = equal(mult.begin(), mult.end(), matrix.begin(), [](double x, double y) {
            return abs(x - y) < 0.000001;
        });
        cout << "Check " << (tr ? "succeeded" : "failed") << endl;
    }
    MPI_Finalize();
    return 0;
}
