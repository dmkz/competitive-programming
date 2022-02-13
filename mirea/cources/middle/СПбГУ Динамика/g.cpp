#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
void setmax(auto &x, auto y) { if (y > x) x = y; }
int main() {
    freopen("longpath.in", "rt", stdin);
    freopen("longpath.out", "wt", stdout);
    int nV, nE; // число вершин и число ребёр
    cin >> nV >> nE;
    vvi prev(1+nV);
    for (int i = 0; i < nE; i++) {
        int from, to; cin >> from >> to;
        prev[to].push_back(from);
    }
    vi dp(nV+1,-1);
    function<int(int)> dfs = [&](int u) {
        if (dp[u] == -1) {
            dp[u] = 0;
            for (int v : prev[u])
                setmax(dp[u], dfs(v)+1);
        }
        return dp[u];
    };
    int max = 0;
    for (int u = 1; u <= nV; u++)
        setmax(max, dfs(u));
    cout << max << endl;;
}