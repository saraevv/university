#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <tuple>
#include <iostream>
#include <ctime>


using namespace std;

int N;

int reduce_matrix(vector<vector<int>> &matrix) {
    int res = 0;

    for (auto &v:matrix) {
        int min = *min_element(v.begin(), v.end());
        if (min != INT_MAX) {
            res += min;
            for (auto &i:v) {
                if (i != INT_MAX) {
                    i -= min;
                }
            }
        }

    }

    for (size_t j = 0; j < N; ++j) {
        int min = 0;
        for (size_t i = 0; i < N; ++i) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        if (min != INT_MAX) {
            res += min;
            for (size_t i = 0; i < N; ++i) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= min;
                }
            }
        }
    }

    return res;
}

void set_inf(vector<vector<int>> &matrix, int row, int col) {
    for (size_t i = 0; i < N; ++i) {
        matrix[row][i] = matrix[i][col] = INT_MAX;
    }

    matrix[col][0] = INT_MAX;
    //matrix[col][row] = INT_MAX;
}

struct Node {
    int cost, v;
    vector<pair<int, int>> way;
    vector<vector<int>> matrix;
};

struct NodeComparator {
    bool operator()(const Node *left, const Node *right) {
        return left->cost > right->cost;
    }
};

tuple<vector<pair<int, int>>, int> task(const vector<vector<int>> &matrix) {
    assert(matrix.size() == N);

    Node *first = new Node;
    first->way = vector<pair<int, int>>();
    first->matrix = matrix;
    first->v = 0;
    first->cost = reduce_matrix(first->matrix);

    priority_queue<Node *, vector<Node *>, NodeComparator> pq;
    pq.push(first);

    while (!pq.empty()) {
        Node *cur = pq.top();
        pq.pop();

        if (cur->way.size() == N - 1) {
            return make_tuple(cur->way, cur->cost);
        } else {
            for (int j = 0; j < N; ++j) {
                if (cur->matrix[cur->v][j] != INT_MAX) {
                    Node *new_node = new Node;
                    new_node->way = cur->way;
                    new_node->way.emplace_back(cur->v, j);
                    new_node->matrix = cur->matrix;
                    set_inf(new_node->matrix, cur->v, j);
                    new_node->v = j;
                    new_node->cost = cur->cost + cur->matrix[cur->v][j] +
                                     reduce_matrix(new_node->matrix);
                    pq.push(new_node);
                }
            }
        }
        delete cur;

    }
    throw logic_error("queue is empty");
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fin >> N;
    vector<vector<int>> matrix = vector<vector<int>>(N, vector<int>(N, INT_MAX));
    vector<pair<int, int>> coord = vector<pair<int, int>>(N);
    for (auto &i:coord) {
        fin >> i.first >> i.second;
    }
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i != j) {
                matrix[i][j] = matrix[j][i] = abs(coord[i].first - coord[j].first) +
                                              abs(coord[i].second - coord[j].second);
            }
        }
    }
    auto res = task(matrix);

    vector<pair<int, int>> way = get<0>(res);
    int cost = get<1>(res);

    fout << cost << '\n';

    for (const auto &p:way) {
        fout << p.first + 1 << ' ';
    }
    fout << way.back().second + 1 << ' ' << way.front().first + 1;
    cerr << clock();

    return 0;
}