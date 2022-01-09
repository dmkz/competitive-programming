#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ld = long double;

struct DSU {
    vi parent, sz;
    DSU(int n) : parent(n+1), sz(n+1, 1)
    {
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int getParent(int u) {
        return parent[u] == u ? u : parent[u] = getParent(parent[u]);
    }
    void connect(int u, int v) {
        u = getParent(u), v = getParent(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v];
        parent[v] = u;
    }
};

int main() {
    // прочитаем вершины и отсортируем их в порядке убывания значений, записанных
    // в этих самых вершинах. Затем будем добавлять эти вершины последовательно в
    // граф. Получается, что добавляемая вершина - минимальная среди добавленных,
    // и нужно посчитать все пути, которые проходят через неё между уже добавленными
    // вершинами. Для этого нужно поддерживать компоненты связностей: их размер.
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,e;
    cin >> n >> e;
    DSU dsu(n);
    vector<pair<int,int>> order;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        order.emplace_back(a,i);
    }
    vvi adj(1+n);
    for (int i = 0; i < e; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sort(all(order), greater<>());
    // начинаем по одной накидывать вершины в порядке убывания числа, записанного в них:
    vi isActive(1+n);
    ld sum = 0;
    for (auto &[a,u] : order) {
        // нужно найти все компоненты связности, с которыми связана вершина u:
        vi components;
        for (auto v : adj[u])
            if (isActive[v])
                components.push_back(dsu.getParent(v));
        sort(all(components));
        components.erase(unique(all(components)), components.end());
        // теперь путь веса `a` проходит через вершину `u`, если он начинается в какой-то
        // компоненте и заканчивается в другой компоненте, либо в вершине `u`
        // считаем все такие пути в переменной `count`:
        ll count = 0, sumSz = 0;
        for (auto p : components) {
            count += dsu.sz[p] * (sumSz + 1LL);
            sumSz += dsu.sz[p];
        }
        // теперь к сумме добавляется `a` умноженное на `count` путей, проходящих через `u`:
        sum += count * a;
        // вершина теперь становится активной (обработанной), соединяем её рёбрами
        // с другими компонентами, состоящими из уже активных вершин:
        isActive[u] = 1;
        for (auto v : adj[u])
            if (isActive[v])
                dsu.connect(u,v);
    }
    // делим на знаменатель и выводим ответ:
    sum /= (n * (n-1LL) / 2);
    cout << setprecision(9) << fixed << sum << endl;
}