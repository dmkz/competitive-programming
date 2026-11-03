#include <bits/stdc++.h>
#include <bits/extc++.h>
using ll = long long;
using ld = long double;
#define int ll
using namespace std;
using tiiii = tuple<int,int,int,int>;
using pii = pair<int,int>;
using vtiiii = vector<tiiii>;
template<typename T> using PQLess = priority_queue<T, vector<T>, greater<T>>;
void solve() {
    // читаем данные и строим граф
    int nVert, nLines;
    cin >> nVert >> nLines;
    vector adj(1+nVert, vtiiii{});
    for (int j = 0; j < nLines; j++) {
        int k, s, p; cin >> k >> s >> p;
        vector<int> vertices(k);
        vector<ll> times(k, s);
        for (int i = 0; i < k; i++)
            cin >> vertices[i];
        for (int i = 1; i < k; i++) {
            cin >> times[i];
            times[i] += times[i-1];
        }
        for (int i = 0; i + 1 < k; i++) {
            int from = vertices[i], to = vertices[i+1];
            adj[from].emplace_back(to, times[i], p, times[i+1] - times[i]);
        }
    }
    // запускаем алгоритм Дейкстры
    const ll inf = (ll)1e18L;
    vector<ll> dist(1+nVert, inf);
    PQLess<pii> pq;
    pq.push({0, 1});
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] <= d)
            continue;
        dist[u] = d;
        for (const auto &[v, t, p, w] : adj[u]) {
            // можем поехать в вершину v начиная с времени t каждые p минут
            // t + k * p >= d
            ll k = (ll)ceil(ld(d - t) / p);
            if (k < 0) k = 0;
            pq.push({t+k*p+w,v});
        }
    }
    // выводим ответ:
    for (int i = 1; i <= nVert; i++) {
        if (dist[i] >= inf) dist[i] = -1;
        cout << dist[i] << ' ';
    }
    cout << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
