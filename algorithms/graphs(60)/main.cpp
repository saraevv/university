#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int end, flow, capacity, cost;
    Edge *reverse;

    Edge(int end, int capacity) : end(end), flow(0), capacity(capacity), cost(0), reverse(nullptr) {};

    Edge(int end, int capacity, int cost) : end(end), flow(0), capacity(capacity), cost(cost), reverse(nullptr) {};
};

bool Levit(vector<vector<Edge *>> &g, vector<pair<int, Edge *>> &way) {
    vector<int> d(g.size(), INT_MAX);
    d[0] = 0;
    vector<int> id(g.size());
    id[0] = 1;
    deque<int> q;
    q.push_back(0);
    vector<char> used(g.size(), 0);
    used[0] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        used[v] = 0;
        id[v] = 1;
        for (auto &i:g[v]) {
            if (i->flow < i->capacity) {
                int cost = i->cost;
                int end = i->end;
                if (d[end] > d[v] + cost) {
                    d[end] = d[v] + cost;
                    /*if (!id[end]) {
                        q.push_back(end);
                    } else if (id[end] == 1) {
                        q.push_front(end);
                    }*/
                    if (used[end] == 0) {
                        q.push_back(end);
                        used[end] = 1;
                    }

                    way[end] = {v, i};
                    id[end] = 1;
                }

            }
        }
    }
    return way[way.size() - 1].first != -1;
}

int max_flow_min_cost(vector<vector<Edge *>> &g) {
    vector<pair<int, Edge *>> way(g.size(), {-1, nullptr});
    int cost = 0;
    while (Levit(g, way)) {
        int min = INT_MAX;
        for (int j = g.size() - 1; j; j = way[j].first) {
            if (way[j].second->capacity - way[j].second->flow < min) {
                min = way[j].second->capacity - way[j].second->flow;
            }
        }
        //cost += min;
        for (int j = g.size() - 1; j; j = way[j].first) {
            way[j].second->flow += min;
            way[j].second->reverse->flow -= min;
            cost += way[j].second->cost * min;
        }

        way.assign(way.size(), {-1, nullptr});
    }

    return cost;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m, x;
    fin >> n >> m;

    vector<vector<Edge *>> g(n + m + 2);

    for (int i = 1; i < n + 1; ++i) {
        fin >> x;
        Edge *orig = new Edge(i, x), *rev = new Edge(0, 0);
        orig->reverse = rev;
        rev->reverse = orig;
        g[0].push_back(orig);
        g[i].push_back(rev);

    }

    for (int i = n + 1; i < n + m + 1; ++i) {
        fin >> x;
        Edge *orig = new Edge(n + m + 1, x), *rev = new Edge(i, 0);
        orig->reverse = rev;
        rev->reverse = orig;
        g[i].push_back(orig);
        g[n + m + 1].push_back(rev);
    }

    for (int i = 1; i < n + 1; ++i) {
        for (int j = n + 1; j < n + m + 1; ++j) {
            fin >> x;
            Edge *orig = new Edge(j, INT_MAX, x), *rev = new Edge(i, 0, -x);
            orig->reverse = rev;
            rev->reverse = orig;
            g[i].push_back(orig);
            g[j].push_back(rev);
        }
    }


    fout << max_flow_min_cost(g);

    return 0;
}
