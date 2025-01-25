#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, nEdges;
    cin >> n >> nEdges;
    vector adj(1+n, vector<int>{});
    while (nEdges --> 0) {
        int u, v; cin >> u >> v;
        if (u == v) continue;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> used(1+n);
    int answ = 0;
    for (int i = 1; i <= n; i++)
        if (!used[i]) {
            // находим количество вершин в компоненте и количество рёбер
            int currVertices = 0, currEdges = 0;
            // функция обхода в глубину
            function<void(int)> dfs = [&](int u) {
                if (used[u])
                    return;
                currVertices++;
                used[u] = 1;
                // посещаем соседей
                for (int v : adj[u]) {
                    currEdges++;
                    dfs(v);
                }
            };
            // запускаем обход в глубину из текущей вершины
            dfs(i);
            currEdges /= 2;
            // обновляем ответ
            // ребёр либо столько же, сколько вершин, либо меньше
            assert(currEdges == currVertices || (currEdges == currVertices - 1));
            if (currEdges == currVertices)
                answ += 1 + currEdges;
            else
                answ += currEdges;
        }
    // выводим ответ:
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}

