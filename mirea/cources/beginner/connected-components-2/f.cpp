#include <bits/stdc++.h>
using namespace std;
void solve() {
    int nV, nE;
    cin >> nV >> nE;
    vector adj(1+nV, vector<int>{});
    while (nE --> 0) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // для каждой компоненты связности считаем число рёбер и её размер
    // ответ для компоненты это разница между числом рёбер и размером
    // дерева на k вершин, где k - размер компоненты
    vector<bool> used(1+nV);
    int answ = 0;
    for (int i = 1; i <= nV; i++)
        if (!used[i]) {
            int currVertices = 0, currEdges = 0;
            // функция для обхода графа в глубину
            function<void(int)> dfs = [&](int u) {
                if (used[u]) return;
                currVertices++;
                used[u] = 1;
                // посещаем соседей
                for (int v : adj[u]) {
                    currEdges++;
                    dfs(v);
                }
            };
            // запуск из вершины i
            dfs(i);
            // увеличиваем ответ
            answ += (currEdges/2) - (currVertices - 1);
        }
    // выводим ответ:
    cout << answ << endl;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}

