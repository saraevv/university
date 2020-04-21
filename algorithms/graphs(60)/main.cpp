#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

struct way {
    int end, capacity, cost, f, reverse;
};

void dfs()

tuple<bool, vector<int>> find_reverse_way(const vector<int> &graph) {

}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    vector<vector<way>> graph(n + m + 2);
    for (int i = 1; i < n + 1; ++i) {
        graph[0].push_back({i, 0, 0, 0, 0});
    }

    for (int i = n + 1; i < n + 1 + m; ++i) {
        graph[i].push_back({n + m + 1, 0, 0, 0, 0});
    }

    for (int i = 0; i < n; ++i) {
        fin >> graph[0][i].capacity;
    }

    for (int i = n + 1; i < n + m + 1; ++i) {
        fin >> graph[i][0].capacity;
    }

    int x;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = n + 1; j < n + 1 + m; ++j) {
            fin >> x;
            graph[i].push_back({j, INT_MAX, x, 0, 0});
        }
    }


    return 0;
}
