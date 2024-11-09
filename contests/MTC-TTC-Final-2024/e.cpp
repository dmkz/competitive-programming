#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;
const int inf = (int)1e9+7;
const bool debug = false;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using spii = set<pii>;
bool intersected(pii a, pii b) {
// являются ли отрезки a и b пересекающимися на прямой?
    auto [ra, la] = a;
    auto [rb, lb] = b;
    int r = std::min(ra, rb);
    int l = std::max(la, lb);
    return l <= r;
}
bool adjacent(pii a, pii b) {
// являются ли отрезки a и b соседними на прямой?
    auto [ra, la] = a;
    auto [rb, lb] = b;
    return ra+1 == lb || rb+1 == la;
}
pii merge(pii a, pii b) {
// объединение двух отрезков
    return {std::max(a.first, b.first), std::min(a.second, b.second)};
}
void insert(spii &s, pii p) {
//  добавить отрезок p в множество отрезков s
    
    // объединяем с отрезком справа от p, если надо:
    // надо найти отрезок справа. Это upper_bound от правой границы
    auto it = s.upper_bound(p);
    if (it != s.end() && (intersected(*it, p) || adjacent(*it, p))) {
        // надо объединить, выкинув отрезок *it из сета
        p = merge(p, *it);
        s.erase(it);
    }
    // объединяем с отрезком слева от p, если надо:
    // это prev(upper_bound(от правой границы))
    it = s.upper_bound(p);
    if (it != s.begin()) { // нельзя делать prev от begin
        it = prev(it);
        if ((intersected(*it, p) || adjacent(*it, p))) {
            // надо объединить, выкинув отрезок *it из сета
            p = merge(p, *it);
            s.erase(it);
        }
    }
    // вставляем объединенный отрезок
    s.insert(p);
}
int getNext(const spii &s, int u) {
    // находим в какой отрезок входит вершина u
    // и возвращаем первую вершину, не входящую в этот отрезок
    auto it = s.lower_bound(pii(u,-1));
    if (it != s.end() && it->second <= u)
        return it->first+1; // правая граница отрезка плюс один
    return u;
}
struct DSU {
    vi par;
    vector<spii> data;
    DSU(int n) : par(1+n, 0), data(1+n)
    {
        for (int u = 1; u <= n; u++) {
            data[u] = {{u,u}};
            par[u] = u;
        }
    }
    int getPar(int u) {
        return par[u] == u ? u : par[u] = getPar(par[u]);
    }
    void connect(int u, int v) {
        // объединение двух компонент
        u = getPar(u), v = getPar(v);
        assert(u != v);
        // меньший сет кладём в больший сет:
        if (data[u].size() < data[v].size())
            swap(u, v);
        for (const auto & p : data[v])
            insert(data[u], p);
        // отмечаем нового предка:
        par[v] = u;
    }
};
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных и сортировка
    int n, k;
    cin >> n >> k;
    DSU dsu(n);
    auto connect = [&](int u, int v) {
        dsu.connect(u, v);
    };
    auto comp = [&](int u) -> spii & {
        return dsu.data[dsu.getPar(u)];
    };
    vector<spii> adj(n+1);
    for (int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        insert(adj[u], pii(v, v));
        insert(adj[v], pii(u, u));
    }
    for (int u = 1; u <= n; u++)
        insert(adj[u], pii(u,u)); // добавляем петлю: петли теперь запрещены
    // основная логика здесь:
    int64_t answ{};
    for (int u = 1; u+1 <= n; u++)
        for (int v = u+1; true; ) {
            // вершина не должна быть запрещена
            // вершина не должна входить в ту же самую компоненту связности
            // ищем её
            // по сути вместо v++ делаем v = getNext(comp(u), getNext(adj[u], v))
            while (v <= n) {
                if (int nextV = getNext(comp(u), getNext(adj[u], v)); nextV == v)
                    break;
                else
                    v = nextV;
            }
            if (v <= n) {
                // нашли её, соединяем u <--> v
                answ += min(u, v);
                connect(u, v);
                v++;
            } else {
                break;
            }
        }
    cout << answ << endl;
}
