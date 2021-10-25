#include <bits/stdc++.h>
using namespace std;

// Очередь с приоритетами в порядке возрастания:
template<typename T>
using PriorityQueue = priority_queue<T,vector<T>,greater<T>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем количество вершин и рёбер:
    int nVert, nEdges;
    cin >> nVert >> nEdges;
    // Читаем сами рёбра в списки смежности:
    vector<vector<pair<int,int>>> adj(1+nVert);
    for (int i = 0; i < nEdges; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        adj[u].push_back({v,cost});
        adj[v].push_back({u,cost});
    }
    // Запускаем алгоритм Дейкстры
    const int64_t INF = 1e18L;
    vector<int64_t> dist(1+nVert, INF); // вектор расстояний до вершин
    vector<int> prev(1+nVert); // prev[i] - откуда пришли в вершину i
    PriorityQueue<tuple<int64_t,int,int>> pq; // очередь с приоритетами, тройки (расстояние, текущая вершина, предыдущая вершина)
    pq.push({0,1,0}); // заносим стартовую вершину
    while (!pq.empty()) {
        // Вынимаем первый элемент из очереди:
        auto [currDist,currVert,prevVert] = pq.top();
        pq.pop();
        // Если уже посещали с лучшим расстоянием, то скипаем:
        if (dist[currVert] <= currDist) continue;
        // Иначе отмечаем текущее расстояние и вершину, из которой пришли:
        dist[currVert] = currDist;
        prev[currVert] = prevVert;
        // Заносим в очередь все смежные вершины:
        for (auto [nextVert, cost] : adj[currVert]) {
            pq.push({currDist+cost,nextVert,currVert});
        }
    }
    // Выводим ответ:
    if (dist[nVert] == INF) {
        cout << "-1\n";
    } else {
        // Успешно добрались до цели
        // Переходим от цели по предыдущим вершинам, пока не дойдём до 0
        vector<int> answ;
        int currVert = nVert;
        while (currVert != 0) {
            answ.push_back(currVert);
            currVert = prev[currVert];
        }
        // Разворачиваем получившийся список и выводим его:
        reverse(answ.begin(),answ.end());
        for (auto item : answ) {
            cout << item << ' ';
        }
        cout << '\n';
    }
    return 0;
}