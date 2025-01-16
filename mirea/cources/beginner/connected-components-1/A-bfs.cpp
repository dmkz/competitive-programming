#include <bits/stdc++.h>
using namespace std;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем входные данные
    int nVert, nEdges; cin >> nVert >> nEdges;
    vector<int> cost(nVert);
    for (int i = 0; i < nVert; i++)
        cin >> cost[i];
    // рёбра сохраняем в списки смежности
    vector adj(nVert, vector<int>{});
    for (int i = 0; i < nEdges; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // решение задачи: нужно найти минимальную стоимость распространения
    // слуха в каждой компоненте связности
    int64_t answ = 0;
    vector<bool> used(nVert);
    for (int s = 0; s < nVert; s++)
        if (!used[s]) { // вершина s ещё не посещена
            // создаём очередь и помещаем туда стартовую вершину
            queue<int> q;
            used[s] = 1;
            q.push(s);
            int currMinCost = INT_MAX; // здесь будем хранить минимум в компоненте
            while (!q.empty()) {
                // вынимаем текущую вершину из начала очереди
                int u = q.front();
                q.pop();
                // обновляем ответ, учитывая стоимость текущей вершины
                setmin(currMinCost, cost[u]);
                // помещаем в очередь всех ещё не помещённых соседей
                for (int v : adj[u])
                    if (!used[v]) {
                        used[v] = 1;
                        q.push(v);
                    }
            }
            // увеличиваем ответ на минимум в этой компоненте
            answ += currMinCost;
        }
    // выводим ответ
    cout << answ << endl;
}
