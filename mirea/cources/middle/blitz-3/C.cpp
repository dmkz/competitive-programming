#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // проверим, что двудольный граф двудольный является связным
    // читаем цвета вершин
    int nV, nE; cin >> nV >> nE;
    vi color(nV+1);
    for (int i = 1; i <= nV; i++)
        cin >> color[i];
    // читаем рёбра и добавляем только те рёбра, по которым
    // можно ходить (на концах разные цвета)
    vvi adj(1+nV);
    for (int i = 1, u, v; i <= nE; i++) {
        cin >> u >> v;
        if (color[u] != color[v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    // запускаем поиск в ширину из вершины 1, чтобы посетить
    // все вершины. если получается, то YES, иначе NO
    // инициализация поиска в ширину:
    vi visited(nV+1);
    vi q = {1};
    visited[1] = 1;
    // алгоритм обхода графа в ширину:
    for (int i = 0; i < isz(q); i++)
        for (int v : adj[q[i]])
            if (!visited[v]) {
                visited[v] = 1;
                q.push_back(v);
            }
    // проверка ответа:
    bool ok = 1;
    for (int u = 1; u <= nV; u++)
        ok &= visited[u];
    cout << (ok ? "YES" : "NO");
}
