#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
auto findDistCnt(int s, int nV, const auto &adj) {
    vector<int> dist(nV+1, INT_MAX);
    vector<long double> cnt(nV+1, 0);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    cnt[s] = 1;
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (int v : adj[u])
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                q.push(v);
            } else if (dist[u] + 1 == dist[v]) {
                cnt[v] += cnt[u];
            }
    }
    return make_pair(move(dist), move(cnt));
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int nV, nE; cin >> nV >> nE;
    vector<pii> edges(nE);
    vector adj(nV+1, vector<int>());
    for (auto &[u, v] : edges) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // расстояние от 1 до всех других вершин + количество путей
    const int s = 1, t = nV;
    auto [distS, cntS] = findDistCnt(s, nV, adj);
    auto [distT, cntT] = findDistCnt(t, nV, adj);
    // считаем ответ для каждой вершины, перебирая рёбра:
    vector<long double> answer(nV+1);
    for (auto [u, v] : edges) {
        // кратчайший путь из s в t проходит через ребро u-v:
        if (distS[u] + 1 + distT[v] == distS[t]) {
            // значит ребро u-v лежит на кратчайшем пути
            // их количество:
            answer[u] += cntS[u] * cntT[v];
            answer[v] += cntS[u] * cntT[v];
        }
        // кратчайший путь из s в t проходит через ребро v-u:
        if (distS[v] + 1 + distT[u] == distS[t]) {
            // значит ребро v-u лежит на кратчайшем пути
            // их количество:
            answer[u] += cntS[v] * cntT[u];
            answer[v] += cntS[v] * cntT[u];
        }
    }
    // находим максимальный ответ:
    long double answ = 0;
    for (int u = 1; u <= nV; u++)
        answ = max(answ, answer[u] / cntS[t]);
    // выводим ответ:
    cout << fixed << setprecision(12);
    cout << answ << endl;
}
