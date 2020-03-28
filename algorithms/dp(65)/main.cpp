#include <fstream>
#include <vector>

using namespace std;

void task(vector<vector<vector<int>>> &A, vector<int> &base, vector<int> &v) {
    for (int i = 0; i < A.size(); ++i) {

        A[i][0][0] = -v[base[1] + i];

        for (int j = 1; j < A[i].size(); ++j) {
            A[i][j][0] = v[base[1] + i];
        }

        for (int j = 0; j < A[i].size(); ++j) {
            if (j == 0) {
                for (int k = 1; k < A[i][j].size(); ++k) {
                    /*int max = 0, num = -1;
                    for (int l = 0; l <= k; ++l) {
                        if (max < v[base[l + 1] + i]) {
                            max = v[base[l + 1] + i];
                            num = l;
                        }
                    }
                    for (int l = 0; l <= k; ++l) {
                        if (l != num) {
                            max -= v[base[l + 1]];
                        }
                    }
                    A[i][j][k] = max;*/
                    int max = INT_MIN;
                    for (int l = 0; l <= i; ++l) {
                        if (max < A[i - l][j][k - 1] - v[base[k + 1] + l]) {
                            max = A[i - l][j][k - 1] - v[base[k + 1] + l];
                        }
                    }
                    A[i][j][k] = max;
                }
            } else {

                for (int k = 1; k < A[i][j].size(); ++k) {
                    int max1 = INT_MIN, max2 = INT_MIN;
                    for (int l = 0; l <= i; ++l) {
                        if (max1 < (A[i - l][j][k - 1] - v[base[k + 1] + l]) &&
                            k >= j) {
                            max1 = A[i - l][j][k - 1] - v[base[k + 1] + l];
                        }
                        if (max2 < (A[i - l][j - 1][k - 1] + v[base[k + 1] + l])) {
                            max2 = A[i - l][j - 1][k - 1] + v[base[k + 1] + l];
                        }
                    }
                    A[i][j][k] = max(max1, max2);
                }
            }
        }
    }
}

int main() {
    ifstream fin("jokers.in");
    ofstream fout("jokers.out");

    int K, C, J, T, N, x;
    fin >> K >> C >> J >> T;
    vector<int> v(C + J + 1);
    for (int i = 0; i < v.size(); ++i) {
        fin >> v[i];
    }
    vector<int> base(K + 1, 0);
    fin >> N;
    for (int i = 0; i < N; ++i) {
        fin >> x;
        ++base[x];
    }
    vector<vector<vector<int>>> A(base[0] + 1, vector<vector<int>>(T + 1, vector<int>(K)));
    task(A, base, v);
    fout << A[base[0]][T][K - 1];

    return 0;
}