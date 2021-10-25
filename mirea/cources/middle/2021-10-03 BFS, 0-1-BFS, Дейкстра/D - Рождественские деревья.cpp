#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    // вставляем все деревья в очередь: будем запускать из них bfs.
    // дополнительно нужно хранить координаты деревьев и координаты людей.
    set<int> trees, people;
    map<int,int> dist;
    queue<pair<int,int>> q;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        q.push({x,0});
        trees.insert(x);
    }
    while (!q.empty()) {
        // вынимаем текущую вершину
        auto [x,d] = q.front();
        q.pop();
        // вставляем нейтральный элемент в мапу расстояний - изначальное расстояние бесконечность
        dist.insert({x,INF});
        // если уже были здесь, то ничего не делаем:
        if (dist[x] <= d) continue;
        // иначе посещаем вершину:
        dist[x] = d;
        if (!trees.count(x)) {
            // если не дерево, то точка x будет человеком:
            people.insert(x);
            if (people.size() == m) break; // выходим когда расставили достаточно людей
        }
        // добавляем соседние вершины в очередь:
        q.push({x-1,d+1});
        q.push({x+1,d+1});
    }
    // сначала считаем суммарное расстояние, затем выводим ответ:
    int64_t minSum = 0;
    for (auto it : people) minSum += dist[it];
    cout << minSum << '\n';
    for (auto it : people) cout << it << ' ';
    cout << endl;
    return 0;
}