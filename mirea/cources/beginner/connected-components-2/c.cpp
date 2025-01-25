#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    int n, k; cin >> n >> k;
    // проводим рёбра i <--> (i+k) и i <--> (i+k+1)
    // находим компоненты связностей (именно буквы, которые входят)
    // сравниваем буквы в компонентах строк s и t
    string s, t;
    cin >> s >> t;
    vector adj(n, vector<int>{});
    for (int i = 0; i < n; i++) {
        if (i+k<n) {
            adj[i].push_back(i+k);
            adj[i+k].push_back(i);
        }
        if (i+k+1<n) {
            adj[i].push_back(i+k+1);
            adj[i+k+1].push_back(i);
        }
    }
    // находим компоненты связности
    vector<bool> used(n);
    bool ok = true;
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            string ss, tt;
            // функция, реализующая обход графа в глубину
            function<void(int)> dfs = [&](int u) {
                if (used[u])
                    return;
                // посещаем вершину, добавляя буквы в компоненту
                used[u] = 1;
                ss += s[u];
                tt += t[u];
                // рекурсивно вызываемся от соседей
                for (int v : adj[u])
                    dfs(v);
            };
            // запускаем dfs из вершины i
            dfs(i);
            // сравниваем буквы компоненты в подстроках s и t
            sort(all(ss));
            sort(all(tt));
            ok &= (ss == tt);
        }
    cout << (ok ? "YES\n" : "NO\n");
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}

