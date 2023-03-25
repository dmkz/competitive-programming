#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using pii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vvi adj(1+n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // вычисляем tin и tout для каждой вершины
    vi tin(n+1), tout(n+1);
    int timer = -1;
    function<void(int,int)> dfs = [&](int u, int p) {
        tin[u] = ++timer;
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u);
        }
        tout[u] = ++timer;
    };
    dfs(1,0);
    // читаем запросы и группируем их по вершинам
    int q; cin >> q;
    vi answ(q);
    vvpii queries(1+n);
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        queries[u].emplace_back(v,i);
    }
    // запускаем поиск в глубину для ответа на все запросы
    vi path;
    function<void(int,int)> solve = [&](int u, int p)
    {
        // заходим в вершину u
        path.push_back(u);
        for (auto &[v, id] : queries[u]) {
            // ищем lca бинпоиском
            int low = 0, high = isz(path);
            while (high - low > 1) {
                int mid = (low+high)/2;
                int x = path[mid];
                if (tin[x] <= tin[v] && tout[v] <= tout[x]) low = mid;
                else high = mid;
            }
            // сохраняем ответ на запрос:
            answ[id] = path[low];
        }
        // запускаемся от поддеревьев:
        for (int v : adj[u]) {
            if (v == p) continue;
            solve(v,u);
        }
        // поднимаемся из вершины u
        path.pop_back();
    };
    solve(1,0);
    // выводим ответы:
    for (auto it : answ)
        cout << it << '\n';
}