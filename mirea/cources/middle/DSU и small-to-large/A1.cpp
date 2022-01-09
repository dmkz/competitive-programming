#include <bits/stdc++.h>
using namespace std;
vector<int> parent, sz;
void init(int n) {
    parent = sz = vector<int>(2 * n + 1);
    for (int i = 1; i < (int)parent.size(); i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}
int getParent(int u) {
    if (parent[u] == u) return u;
    return parent[u] = getParent(parent[u]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        // обрабатываем запросы:
        init(n);
        vector<vector<int>> next(2*n+1);
        int root = n;
        for (int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            // создаём новый корень и подвешиваем представителей поддеревьев u и v к нему:
            root++;
            u = getParent(u), v = getParent(v);
            next[root].push_back(u);
            next[root].push_back(v);
            parent[u] = root;
            parent[v] = root;
        }
        // обход дерева:
        function<void(int)> dfs = [&](int u) {
            for (int v : next[u]) {
                dfs(v);
            }
            if (next[u].empty()) {
                // это лист
                cout << u << ' ';
            }
        };
        dfs(root);
        cout << '\n';
    }
    return 0;
}