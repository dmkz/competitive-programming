#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vvi = vector<vector<int>>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем число вершин и список смежности
    int n; cin >> n;
    vvi adj(1+n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Вершину с максимальной степенью мы берём за корень    
    int root = 1;
    for (int u = 2; u <= n; u++)
        if (isz(adj[u]) > isz(adj[root]))
            root = u;
    // Нам выгодно начинать путь с какого-то листа и идти
    // до какого-то листа. Обходим дерево, к ответу
    // добавляется (количество детей)/2, потому что половину
    // рёбер мы посетим снизу-вверх, а вторую половину
    // сверху-вниз
    int answ = 0;
    function<void(int,int)> dfs = [&](int u, int p) {
        int nChild = 0;
        for (int v : adj[u])
            if (v != p) {
                dfs(v,u);
                nChild++;
            }
        answ += (nChild / 2);
    };
    dfs(root, 0);
    // особый случай: если у корня нечётное число поддеревьев,
    // то остался связный список который мы проходим за один
    if (isz(adj[root]) % 2 == 1)
        answ++;
    // выводим ответ. незабываем, что одна телепортация
    // халявная (самая первая, когда мы стартуем из любой вершины)
    cout << max(0, answ-1) << endl;
}
