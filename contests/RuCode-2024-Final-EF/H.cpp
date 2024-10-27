#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
/* из третьего примера можем понять, что пары рассматриваются из уникальных
без повторов (A, B) и (B, A)
1 2
1 3
1 4
2 3
2 4
3 4
*/
main() {
    // читаем граф в виде списка смежностей
    int nV, nE;
    cin >> nV >> nE;
    vvi adj(nV+1);
    for (int i = 0, u, v; i < nE; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // находим размеры компонент связностей:
    vi sizes, visited(nV+1);
    for (int u = 1; u <= nV; u++) {
        if (!visited[u]) {
            vi q = {u};
            visited[u] = 1;
            for (int i = 0; i < (int)q.size(); i++)
                for (int v : adj[q[i]])
                    if (!visited[v]) {
                        visited[v] = 1;
                        q.push_back(v);
                    }
            sizes.push_back((int)q.size());
        }
    }
    // считаем, сколько пар (А, B) лежат в разных компонентах связности
    ll p = 0, q = nV * (nV - 1LL) / 2;
    for (int i = 0; i + 1 < (int)sizes.size(); i++) {
        nV -= sizes[i];
        p += sizes[i] * 1LL * nV;
    }
    p = q - p;
    ll g = gcd(p, q);
    cout << p/g << " " << q/g << endl;
}
