#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

struct Vertex {
    bool init_color;
    int time_left, blue_time, red_time, num;

    Vertex() {}

    // B = true
    // P = false
    Vertex(char c, int rc, int tb, int tp, int num) :
            time_left(rc), blue_time(tb), red_time(tp), num(num) {
        init_color = (c == 'B');
    }

    pair<bool, int> get_color(int t) {
        if (t < time_left) {
            return {init_color, time_left - t};
        }
        t -= time_left;
        int cur = t % (blue_time + red_time);
        if (init_color) {
            if (cur < red_time) {
                return {false, red_time - cur};
            } else {
                return {true, blue_time + red_time - cur};
            }
        } else {
            if (cur < blue_time) {
                return {true, blue_time - cur};
            } else {
                return {false, blue_time + red_time - cur};
            }
        }
    }
};

struct Edge {
    Vertex begin, end;
    int time;

    Edge(Vertex &begin, Vertex &end, int time) : begin(begin), end(end), time(time) {}

    int travel_time(int t) {
        pair<bool, int> b = begin.get_color(t), e = end.get_color(t);
        // cant move
        if (begin.red_time == end.blue_time && begin.blue_time == end.red_time &&
            b.second == e.second) {
            return -1;
        }
        //can move already
        if (b.first == e.first) {
            return t + this->time;
        }
        t += min(b.second, e.second);

        if (b.second != e.second) {
            return t + this->time;
        }
        b = begin.get_color(t), e = end.get_color(t);
        t += min(b.second, e.second);
        return t + this->time;
        /*int rem = time;
        do {
            int min = std::min(b.second, e.second);
            if (b.first == e.first) {
                if (min >= rem) {
                    t += min;
                    break;
                }
                rem -= min;
            }
            t += min;
            b = begin.get_color(t);
            e = end.get_color(t);
        } while (rem);*/
    }
};


vector<pair<int, int>> task(int begin, vector<vector<Edge>> &ve) {
    vector<pair<int, int>> way(ve.size(), {INT_MAX, -1});
    way[begin] = {0, -1};
    set<pair<int, int>> s;
    s.insert({0, begin});
    while (!s.empty()) {
        int v = s.begin()->second;
        int time = s.begin()->first;
        s.erase(s.begin());
        for (auto &i:ve[v]) {
            int u = i.end.num;
            int time_to = i.travel_time(time);
            if (time_to != -1 && way[u].first > time_to) {
                s.erase({way[u].first, u});
                way[u].first = time_to;
                way[u].second = v;
                s.insert({way[u].first, u});
            }
        }
    }
    return way;
}


int main() {
    ifstream fin("lights.inp");
    ofstream fout("lights.out");

    int start, end, n, m;

    fin >> start >> end >> n >> m;
    --start;
    --end;

    vector<Vertex> vv(n);
    char c;
    int rc, tb, tp, num = 0;
    for (auto &i:vv) {
        fin >> c >> rc >> tb >> tp;
        i = Vertex(c, rc, tb, tp, num);
        ++num;
    }

    vector<vector<Edge>> ve(n, vector<Edge>());
    int edge_begin, edge_end, edge_time;
    for (size_t i = 0; i < m; ++i) {
        fin >> edge_begin >> edge_end >> edge_time;
        --edge_begin;
        --edge_end;
        ve[edge_begin].emplace_back(vv[edge_begin], vv[edge_end], edge_time);
        ve[edge_end].emplace_back(vv[edge_end], vv[edge_begin], edge_time);
    }

    vector<pair<int, int>> ans = task(start, ve);
    if (ans[end].first != -1) {
        fout << ans[end].first << '\n';
        vector<int> way;
        int i = end;
        while (i != -1) {
            way.push_back(i);
            i = ans[i].second;
        }
        reverse(way.begin(), way.end());
        for (const auto &j:way) {
            fout << j + 1 << ' ';
        }
    } else {
        fout << '0';
    }

    return 0;
}
