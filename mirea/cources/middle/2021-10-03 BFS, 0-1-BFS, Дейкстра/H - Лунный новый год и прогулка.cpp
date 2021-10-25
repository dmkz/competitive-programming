#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем все исходные данные:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m; cin >> n >> m;
    vector<vector<int>> adj(1+n);
    for (int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // начинаем применять алгоритм Дейкстры/Прима
    // каждый раз нужно находить вершину с минимальным номером из ещё непосещенных,
    // но смежных с посещенными
    vector<bool> used(n+1);
    priority_queue<int,vector<int>,greater<int>> pq;
    pq.push(1);
    while (pq.size()) {
        // вынимаем вершину:
        auto vert = pq.top();
        pq.pop();
        // уже посещали её, нет смысла ещё раз обрабатывать:
        if (used[vert]) continue;
        // иначе обрабатываем:
        cout << vert << ' ';
        used[vert] = 1;
        for (int v : adj[vert]) pq.push(v);
    }
}