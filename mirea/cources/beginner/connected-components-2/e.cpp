#include <bits/stdc++.h>
using namespace std;
void solve() {
    int nVert, nEdges, nColors;
    cin >> nVert >> nEdges >> nColors;
    vector<int> color(1+nVert);
    for (int i = 1; i <= nVert; i++)
        cin >> color[i];
    // читаем рёбра и формируем списки смежности
    vector adj(nVert+1, vector<int>{});
    while (nEdges --> 0) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // решаем задачу
    vector<bool> used(1+nVert);
    int answ = 0;
    for (int i = 1; i <= nVert; i++)
        if (!used[i]) {
            // для каждой компоненты нужно посчитать количество
            // каждого цвета и перекрасить все носки в самый
            // частовстречающийся цвет
            map<int, int> colorsInComponent;
            int compSize = 0;
            // рекурсивная функция обхода в глубину
            function<void(int)> dfs = [&](int u) {
                if (used[u])
                    return;
                // обрабатываем текущую вершину
                colorsInComponent[color[u]]++;
                compSize++;
                used[u] = 1;
                // запускаемся рекурсивно от соседей
                for (int v : adj[u])
                    dfs(v);
            };
            // запускаем обход в глубину
            dfs(i);
            // находим ответ для текущей компоненты
            int currAnsw = compSize;
            for (const auto &[_, count] : colorsInComponent)
                currAnsw = min(currAnsw, compSize - count);
            answ += currAnsw;
        }
    // выводим ответ для графа в целом
    cout << answ << endl;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}

