#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

//struct pair_hash {
//    template<typename T1, typename T2>
//    size_t operator()(const pair<T1, T2> &p) const {
//        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
//    }
//};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int r, c, n, x, y;
    fin >> r >> c >> n;
    vector<pair<int, int>> vp;
    for (int i = 0; i < n; ++i) {
        fin >> x >> y;
        vp.emplace_back(x - 1, y - 1);
    }

    sort(vp.begin(), vp.end(), [](pair<int, int> x, pair<int, int> y) {
        return x.first != y.first ? x.first < y.first : x.second < y.second;
    });

    //unordered_map<pair<int, int>, int, pair_hash> m;
    unordered_map<int, unordered_map<int, int>> m;
    for (int i = 0; i < n; ++i) {
        //m.insert({{vp[i].first, vp[i].second}, i});
        m[vp[i].first][vp[i].second] = i;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            pair<int, int> cur = {2 * vp[j].first - vp[i].first, 2 * vp[j].second - vp[i].second};
            auto it1 = m.find(cur.first);
            if (it1 != m.end()) {
                auto it2 = it1->second.find(cur.second);
                if (it2 != it1->second.end()) {
                    dp[i][j] = dp[j][it2->second] + 1;
                } else {
                    dp[i][j] = 2;
                }
            } else {
                dp[i][j] = 2;
            }
        }
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (dp[i][j] != 2 && dp[i][j] > ans) {
                int dy = vp[i].first - vp[j].first,
                        dx = vp[i].second - vp[j].second;
                if ((vp[i].first + dy >= r || vp[i].second + dx >= c || vp[i].second + dx < 0) &&
                    (vp[i].first - dp[i][j] * dy < 0 || vp[i].second - dp[i][j] * dx < 0 ||
                     vp[i].second - dp[i][j] * dx >= c)) {
                    ans = dp[i][j];
                }
            }
        }
    }
    fout << ans;
    return 0;
}
