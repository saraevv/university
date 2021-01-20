#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "mpi.h"

using namespace std;

double f1(double y) {
    return sin(y);
}

double f2(double y) {
    return y;
}

double f3(double x) {
    return x * x * x;
}

double f4(double x) {
    return x * x;
}

double F(double x, double y) {
    return x * y;
}

const int N = 200;
const double EPS = 1e-3;

void Decomposition1D() {
    int my_rank, rank_count;
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_count);

    double h = 1.0 / (N + 1.0);

    if (N % rank_count) {
        if (my_rank == 0) {
            cout << "Invalid number of processes" << endl;
        }
        return;
    }

    const int height = N / rank_count;
    vector<vector<double>> u(height + 2, vector<double>(N + 2));
    if (my_rank == 0) {
        for (int j = 1; j <= N; ++j) {
            u.front()[j] = f3(j * h);
        }
    }

    if (my_rank == rank_count - 1) {
        for (int j = 1; j <= N; ++j) {
            u.back()[j] = f4(j * h);
        }
    }
    for (int i = 0; i <= height + 1; ++i) {
        u[i].front() = f1(h * (my_rank * height + i));
        u[i].back() = f2(h * (my_rank * height + i));
    }

    MPI_Barrier(MPI_COMM_WORLD);

    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();

    int iterations = 0;
    double overall_diff = 0;
    do {
        if (my_rank != 0) {
            MPI_Sendrecv(u[1].data() + 1, N, MPI_DOUBLE, my_rank - 1, 98,
                         u[0].data() + 1, N, MPI_DOUBLE, my_rank - 1, 99,
                         MPI_COMM_WORLD, &status);
        }
        if (my_rank != rank_count - 1) {
            MPI_Sendrecv(
                    u[height].data() + 1, N, MPI_DOUBLE, my_rank + 1, 99,
                    u[height + 1].data() + 1, N, MPI_DOUBLE, my_rank + 1, 98,
                    MPI_COMM_WORLD, &status);
        }

        double max_diff = 0;
        for (int i = 1; i <= height; ++i) {
            for (int j = 1; j <= N; ++j) {
                double prev = u[i][j];
                u[i][j] = (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] -
                           h * h * F(h * j, h * (my_rank * height + i))) / 4.0;
                max_diff = max(max_diff, abs(u[i][j] - prev));
            }
        }

        MPI_Allreduce(
                &max_diff, &overall_diff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        ++iterations;
    } while (overall_diff > EPS);
    chrono::steady_clock::time_point end_time = chrono::steady_clock::now();

    MPI_Barrier(MPI_COMM_WORLD);

    if (my_rank != 0) {
        for (int i = 0; i < height + 2; ++i) {
            MPI_Send(u[i].data(), N + 2, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD);
        }
        return;
    }

    chrono::duration<double> calc_time = end_time - start_time;
    cout << "1D decomposition: " << calc_time.count() << "s " << iterations << " iterations\n";

    ofstream output("result1.csv");
    output << fixed;

    for (size_t i = 0; i < u.front().size(); ++i) {
        if (i) {
            output << ',';
        }
        output << u.front()[i];
    }
    output << '\n';

    for (int proc = 0; proc < rank_count; ++proc) {
        if (proc != 0) {
            for (int i = 0; i < height + 2; ++i) {
                MPI_Recv(u[i].data(), N + 2, MPI_DOUBLE, proc,
                         100, MPI_COMM_WORLD, &status);
            }
        }
        for (int i = 1; i <= height; ++i) {
            for (size_t j = 0; j < u.front().size(); ++j) {
                if (j) {
                    output << ',';
                }
                output << u[i][j];
            }
            output << '\n';
        }
    }
    for (size_t i = 0; i < u.front().size(); ++i) {
        if (i) {
            output << ',';
        }
        output << u.back()[i];
    }
    output << '\n';
}

void Decomposition2D() {
    int my_rank, rank_count;
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &rank_count);

    double step = 1.0 / (N + 1.0);
    auto real = [step](int index) {
        return index * step;
    };

    int rank_count_x, rank_count_y;
    if (my_rank == 0) {
        cin >> rank_count_y >> rank_count_x;
    }
    MPI_Bcast(&rank_count_x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&rank_count_y, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank_count_x * rank_count_y != rank_count ||
        N % rank_count_x != 0 || N % rank_count_y != 0) {
        if (my_rank == 0) {
            cout << "Invalid number of processes" << endl;
        }
        return;
    }
    const int height = N / rank_count_y;
    const int width = N / rank_count_x;
    const int proc_x = my_rank % rank_count_x;
    const int proc_y = my_rank / rank_count_x;
    vector<vector<double>> u(height + 2, vector<double>(width + 2));
    if (proc_y == 0) {
        for (int j = 0; j <= width + 1; ++j) {
            u.front()[j] = f3(real(proc_x * width + j));
        }
    }
    if (proc_y == rank_count_y - 1) {
        for (int j = 0; j <= width + 1; ++j) {
            u.back()[j] = f4(real(proc_x * width + j));
        }
    }
    if (proc_x == 0) {
        for (int i = 0; i <= height + 1; ++i) {
            u[i].front() = f1(real(proc_y * height + i));
        }
    }
    if (proc_x == rank_count_x - 1) {
        for (int i = 0; i <= height + 1; ++i) {
            u[i].back() = f2(real(proc_y * height + i));
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
    int iterations = 0;
    double overall_diff = 0;
    vector<double> send_buf(height), recv_buf(height);
    do {
        if (proc_y != 0) {
            MPI_Sendrecv(
                    u[1].data() + 1, width, MPI_DOUBLE, my_rank - rank_count_x, 198,
                    u[0].data() + 1, width, MPI_DOUBLE, my_rank - rank_count_x, 199,
                    MPI_COMM_WORLD, &status);
        }
        if (proc_y != rank_count_y - 1) {
            MPI_Sendrecv(
                    u[height].data() + 1, width, MPI_DOUBLE, my_rank + rank_count_x, 199,
                    u[height + 1].data() + 1, width, MPI_DOUBLE, my_rank + rank_count_x, 198,
                    MPI_COMM_WORLD, &status);
        }
        if (proc_x != 0) {
            for (int i = 0; i < height; ++i) {
                send_buf[i] = u[i + 1][1];
            }
            MPI_Sendrecv(send_buf.data(), height, MPI_DOUBLE, my_rank - 1, 200,
                         recv_buf.data(), height, MPI_DOUBLE, my_rank - 1, 201,
                         MPI_COMM_WORLD, &status);
            for (int i = 0; i < height; ++i) {
                u[i + 1][0] = recv_buf[i];
            }
        }
        if (proc_x != rank_count_x - 1) {
            for (int i = 0; i < height; ++i) {
                send_buf[i] = u[i + 1][width];
            }
            MPI_Sendrecv(send_buf.data(), height, MPI_DOUBLE, my_rank + 1, 201,
                         recv_buf.data(), height, MPI_DOUBLE, my_rank + 1, 200,
                         MPI_COMM_WORLD, &status);
            for (int i = 0; i < height; ++i) {
                u[i + 1][width + 1] = recv_buf[i];
            }
        }

        double max_diff = 0;
        for (int i = 1; i <= height; ++i) {
            for (int j = 1; j <= width; ++j) {
                double prev = u[i][j];
                u[i][j] = (u[i - 1][j] + u[i + 1][j] + u[i][j - 1] + u[i][j + 1] -
                           step * step * F(real(j), real(proc_y * height + i))) / 4.0;
                max_diff = max(max_diff, abs(u[i][j] - prev));
            }
        }

        MPI_Allreduce(
                &max_diff, &overall_diff, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        ++iterations;
    } while (overall_diff > EPS);
    chrono::steady_clock::time_point end_time =
            chrono::steady_clock::now();

    MPI_Barrier(MPI_COMM_WORLD);

    if (my_rank != 0) {
        for (int i = 0; i < height + 2; ++i) {
            MPI_Send(u[i].data(), width + 2, MPI_DOUBLE, 0,
                     202, MPI_COMM_WORLD);
        }
        return;
    }

    chrono::duration<double> calc_time = end_time - start_time;
    cout << "2D decomposition: " << calc_time.count() << "s " << iterations << " iterations\n";

    ofstream output("result2.csv");
    output << fixed;
    vector<vector<double>> u_res(N + 2, vector<double>(N + 2));
    for (int proc = 0; proc < rank_count; ++proc) {
        int cur_proc_x = proc % rank_count_x;
        int cur_proc_y = proc / rank_count_x;
        if (proc != 0) {
            for (int i = 0; i < height + 2; ++i) {
                MPI_Recv(u[i].data(), width + 2, MPI_DOUBLE, proc,
                         202, MPI_COMM_WORLD, &status);
            }
        }
        if (cur_proc_x == 0) {
            for (int i = 1; i <= height; ++i) {
                u_res[cur_proc_y * height + i].front() = u[i].front();
            }
        }
        if (cur_proc_x == rank_count_x - 1) {
            for (int i = 1; i <= height; ++i) {
                u_res[cur_proc_y * height + i].back() = u[i].back();
            }
        }
        if (cur_proc_y == 0) {
            copy(u.front().begin(), u.front().end(),
                 u_res.front().begin() + cur_proc_x * width);
        }
        if (cur_proc_y == rank_count_y - 1) {
            copy(u.back().begin(), u.back().end(),
                 u_res.back().begin() + cur_proc_x * width);
        }
        for (int i = 1; i <= height; ++i) {
            copy(u[i].begin(), u[i].end(),
                 u_res[cur_proc_y * height + i].begin() +
                 cur_proc_x * width);
        }
    }
    for (size_t i = 0; i < N + 2; ++i) {
        for (size_t j = 0; j < N + 2; ++j) {
            if (j) {
                output << ',';
            }
            output << u_res[i][j];
        }
        output << '\n';
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    Decomposition1D();
    Decomposition2D();
    MPI_Finalize();
}