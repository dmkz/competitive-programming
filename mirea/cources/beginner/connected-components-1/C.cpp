#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем входные данные
    int nVert, nEdges, nCapitals;
    cin >> nVert >> nEdges >> nCapitals;
    // читаем номера столиц и отмечаем какие вершины являются столицами
    vector<bool> isCapital(nVert);
    for (int i = 0; i < nCapitals; i++) {
        int c; cin >> c;
        c--;
        isCapital[c] = 1;
    }
    // рёбра сохраняем в списки смежности
    vector adj(nVert, vector<int>{});
    for (int i = 0; i < nEdges; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // решение задачи: нужно найти компоненты связности
    // есть компоненты, в которых есть столица, и есть компоненты, в которых
    // их нет
    // Пусть размер компоненты равен sz. Тогда в ней может быть
    // sz * (sz-1)/2 ребёр. Мы можем дополнить каждую компоненту
    // до максимального количества возможных ребёр. Нужно посчитать
    // количество ребёр для каждой компоненты: это сумма размеров
    // списокв смежности, делённая пополам (так как каждое ребро
    // посчитано дважды)
    // также все компоненты, в которых нет столиц, присоединяем к максимальной
    // компоненте со столицей
    vector<bool> used(nVert);
    vector<pair<int,int>> components;
    int freeVertices = 0, usedEdgesBetweenFreeVertices = 0;
    for (int s = 0; s < nVert; s++)
        if (!used[s]) { // вершина s ещё не посещена
            // создаём очередь и помещаем туда стартовую вершину
            queue<int> q;
            used[s] = 1;
            q.push(s);
            int numExistingEdges = 0; // количество ребёр в компоненте
            int sz = 0; // размер компоненты
            bool hasCapital = false; // есть ли столица в компоненте
            while (!q.empty()) {
                // вынимаем текущую вершину из начала очереди
                int u = q.front();
                q.pop();
                // обновляем ответ, учитывая количество ребёр для текущей вершины
                numExistingEdges += int(adj[u].size());
                sz++;
                hasCapital |= isCapital[u];
                // помещаем в очередь всех ещё не помещённых соседей
                for (int v : adj[u])
                    if (!used[v]) {
                        used[v] = 1;
                        q.push(v);
                    }
            }
            // сохраняем информацию о компоненте
            if (hasCapital)
                components.emplace_back(sz, numExistingEdges);
            else {
                freeVertices += sz;
                usedEdgesBetweenFreeVertices += numExistingEdges;
            }
        }
    // сортируем компоненты по размеру в порядке убывания
    sort(all(components), greater<>());
    // все бесплатные вершины присоединяем к максимальной компоненте
    components[0].first += freeVertices;
    components[0].second += usedEdgesBetweenFreeVertices;
    // считаем ответ, дополняя каждую компоненту до полного графа:
    int64_t answ = 0;
    for (const auto &[sz, edges] : components)
        answ += (sz * (sz - 1) / 2) - (edges / 2);
    // выводим ответ
    cout << answ << endl;
}
