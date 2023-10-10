#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные: типы вершин и список смежности графа
    int nV, nE; cin >> nV >> nE;
    vector<int> vertexType(nV+1);
    for (int u = 1; u <= nV; u++)
        cin >> vertexType[u];
    vvi adj(1+nV);
    for (int i = 0, u, v; i < nE; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // решаем задачу: мы можем посетить почти все вершины, кроме вытянутых списков из
    // вершин степени <= 2, которые ведут в дэпо в итоге
    // при этом нам повезёт, если мы встретим "островную вершину", в которой сможем
    // развернуться. Нам нужно стартануть из каждой конечной вершины (у которой ровно 1 ребро)
    // и посчитать длину пути от неё до первого разворота. Назовём это "хвостом", а число вершин
    // до первого разворота - длиной хвоста. Мы можем выбрать два максимальных хвоста, и
    // посетить их (в одном хвосте начнём, в другом - закончим), а все остальные хвосты придётся
    // выкинуть. Итого, задача: найти длины всех хвостов, посортить их и взять два максимума
    vector<int> used(1+nV), tails;
    for (int s = 1; s <= nV; s++)
        if (isz(adj[s]) == 1) {
            int len = 0;
            function<void(int,int)> dfs = [&](int u, int p) {
                if (used[u] || isz(adj[u]) > 2 || vertexType[u] == 1)
                    return;
                used[u] = 1;
                len++;
                for (int v : adj[u])
                    if (v != p)
                        dfs(v,u);
            };
            dfs(s,0);
            tails.push_back(len);
        }
    // сортируем хвосты и берём два максимума
    sort(all(tails), greater<>());
    int answ = nV;
    while (isz(tails) > 2) {
        answ -= tails.back();
        tails.pop_back();
    }
    cout << answ << endl;
    return 0;
}
