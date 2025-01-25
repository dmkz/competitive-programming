#include <bits/stdc++.h>
using namespace std;
void solve() {
    int nUsers, nGroups;
    cin >> nUsers >> nGroups;
    vector adj(nUsers+1, vector<int>{});
    while (nGroups --> 0) {
        // мы прочитаем элементы группы g[0], g[1], g[2], ..., g[k-1]
        // и соединим рёбрами соседей: g[0]<-->g[1]<-->g[2]<-->...<-->g[k-1]
        int groupSize; cin >> groupSize;
        vector<int> group(groupSize);
        for (int i = 0; i < groupSize; i++) {
            cin >> group[i];
            if (i-1 >= 0) {
                int u = group[i-1], v = group[i];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
    }
    // теперь нужно найти размер каждой компоненты связности
    // и к какой компоненте каждая вершина принадлежит
    vector<int> idComp(nUsers+1);
    int numComps = 0;
    vector<int> compSize = {0};
    for (int i = 1; i <= nUsers; i++) {
        if (!idComp[i]) {
            // найдена новая компонента, создаём её:
            numComps++;
            compSize.push_back(0);
            // функция для обхода графа в глубину:
            function<void(int)> dfs = [&](int u) {
                if (idComp[u]) // если уже посещена, то ничего не делаем
                    return;
                // увеличиваем размер компоненты и отмечаем компоненту для u
                compSize.back()++;
                idComp[u] = numComps;
                // запускаемся рекурсивно от соседей
                for (int v : adj[u])
                    dfs(v);
            };
            // запуск обхода графа в глубину из вершины i
            dfs(i);
        }
        // выводим ответ:
        int id = idComp[i];
        cout << compSize[id] << ' ';
    }
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}

