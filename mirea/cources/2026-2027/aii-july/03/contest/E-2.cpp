#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
int lowpos(const auto &v, const auto &x) { return int(lower_bound(all(v), x) - v.begin()); }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }

// система непересекающихся множеств: каждому отрезку [l, r) соответствует
// своя вершина в дереве, которая хранит длину этого отрезка
struct DSU {
    vector<int> par, len, sz;
    DSU(int n)
        : par(n), len(n, 0), sz(n, 1)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    // получение представителя с эвристикой сжатия путей:
    int getPar(int u) {
        return u == par[u] ? u : par[u] = getPar(par[u]);
    }
    // объединение двух множеств с эвристикой по их размеру:
    void merge(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        len[u] += len[v];
    }
    // функции для работы с длиной отрезков:
    void addLen(int u, int x) {
        len[getPar(u)] += x;
    }
    int getLen(int u) {
        return len[getPar(u)];
    }
};

void solve() {
    // читаем запросы, собираем множество используемых координат:
    int n, q; cin >> n >> q;
    vector<pair<int,int>> queries(q);
    vector<int> x = {1, n+1};
    for (auto &[l, r] : queries) {
        char c; cin >> c >> l >> r;
        x.push_back(l);
        x.push_back(r+1);
    }
    // делаем сжатие координат:
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    // отмечаем, какие отрезки заняты после всех запросов:
    const int numSegments = isz(x)-1;
    vector<int> occupied(numSegments, 0);
    for (auto &[l, _] : queries) {
        l = lowpos(x, l);
        occupied[l] = 1;
    }
    // инициализируем DSU, находим лучший ответ после всех запросов:
    DSU dsu(numSegments);
    int best = 0;
    for (int i = 0; i < numSegments; i++) {
        if (!occupied[i]) {
            setmax(best, x[i+1] - x[i]);
            dsu.addLen(i, x[i+1] - x[i]);
        }
    }
    // начинаем обрабатывать запросы в обратном порядке
    // теперь один запрос [l, r] объединяет три отрезка: l-1, l, l+1
    // правая граница не используется, так как в сжатых координатах l == r
    vector<int> answ(isz(queries));
    for (int queryId = isz(queries)-1; queryId >= 0; queryId--) {
        // текущее состояние соответствует ответу после queryId-го запроса
        // в исходном порядке, поэтому сохраняем best до "отката":
        answ[queryId] = best;
        // освобождаем текущий отрезок:
        int i = queries[queryId].first;
        dsu.addLen(i, x[i+1] - x[i]);
        occupied[i] = 0;
        // объединяем текущий отрезок с его соседом слева:
        if (i - 1 >= 0 && !occupied[i-1])
            dsu.merge(i-1, i);
        // объединяем текущий отрезок с его соседом справа:
        if (i + 1 < numSegments && !occupied[i+1])
            dsu.merge(i, i+1);
        // обновляем ответ:
        setmax(best, dsu.getLen(i));
    }
    // выводим ответ:
    for (int i = 0; i < isz(answ); i++)
        cout << answ[i] << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
