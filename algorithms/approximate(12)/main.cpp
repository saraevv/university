#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <iostream>

using namespace std;

#define INF numeric_limits<double>::max()

#define MAX1M_CH3CH3TK1N

void calc_cycle(vector<int> &cycle, vector<vector<double>> &costs, int i) {
    for (size_t j = 0; j < costs.size(); ++j) {
        if (costs[i][j] != INF) {
            cycle.push_back(j);
            costs[i][j] = costs[j][i] = INF;
            calc_cycle(cycle, costs, j);
        }
    }
}

vector<int> Eulerian_cycle(const vector<pair<int, int>> &min_ostov,
                           const vector<vector<double>> &costs) {
    vector<int> cycle = {0};
    vector<vector<double>> ostov_costs(costs.size(), vector<double>(costs.size(), INF));
    for (const auto &p:min_ostov) {
        ostov_costs[p.first][p.second] = ostov_costs[p.second][p.first] =
                costs[p.first][p.second];
    }
    calc_cycle(cycle, ostov_costs, 0);
    return cycle;

}

class disjoint_set_union {
public:
    int components_;
    int *size_;
    int *parent_;

    explicit disjoint_set_union(const int n) {
        components_ = n;
        size_ = new int[n + 1];
        parent_ = new int[n + 1];
        for (auto i = 1; i <= n; ++i) {
            size_[i] = 1;
            parent_[i] = i;
        }
    }

    int get_components() const {
        return components_;
    }

    int find(const int x) const {
        if (x == parent_[x]) {
            return x;
        }
        parent_[x] = find(parent_[x]);
        return parent_[x];
    }

    void union_set(int x, int y) {
        x = find(x);
        y = find(y);

        if (x != y) {
            if (size_[x] < size_[y]) {
                std::swap(x, y);
            }
            --components_;
            parent_[y] = x;
            size_[x] += size_[y];
        }
    }
};

inline double calculate_length(const vector<pair<int, int>> &coordinates, int i, int j) {
    return sqrt(static_cast<double>(coordinates[i].first - coordinates[j].first) *
                static_cast<double>(coordinates[i].first - coordinates[j].first) +
                static_cast<double>(coordinates[i].second - coordinates[j].second) *
                static_cast<double>(coordinates[i].second - coordinates[j].second));
}


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n;
    fin >> n;

    vector<pair<int, int>> coordinates(n);
    for (int i = 0; i < n; ++i) {
        fin >> coordinates[i].first >> coordinates[i].second;
    }
    cerr << "Input coord: " << clock() << '\n';
    vector<vector<double>> costs(n, vector<double>(n));
    vector<pair<double, pair<int, int>>> graph;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            double cost = calculate_length(coordinates, i, j);
            graph.push_back({cost, {i, j}});
            costs[i][j] = cost;
            costs[j][i] = cost;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        costs[i][i] = INF;
    }
    cerr << "Calc graph and costs: " << clock() << '\n';
    sort(graph.begin(), graph.end());
    cerr << "Sort: " << clock() << '\n';
    vector<pair<int, int>> min_ostov;
    disjoint_set_union dsu(n);

    for (const auto &p:graph) {
        int v = p.second.first, u = p.second.second;
        if (dsu.find(v + 1) != dsu.find(u + 1)) {
            min_ostov.emplace_back(v, u);
            dsu.union_set(v + 1, u + 1);
        }
    }
    cerr << "Min ostov: " << clock() << '\n';

    vector<int> eulerian_cycle = Eulerian_cycle(min_ostov, costs);
    cerr << "Eulerian cycle: " << clock() << '\n';

    double total_cost = 0.0;
    for (int i = 1; i < n; ++i) {
        total_cost += costs[eulerian_cycle[i]][eulerian_cycle[i - 1]];
    }
    total_cost += costs[eulerian_cycle[n - 1]][eulerian_cycle[0]];
    fout << fixed << setprecision(3) << total_cost << '\n';
    for (const auto &v:eulerian_cycle) {
        fout << v + 1 << ' ';
    }
    cerr << "total: " << clock() << '\n';
    return 0;
}