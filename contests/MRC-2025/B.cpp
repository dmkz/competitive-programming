// Задача: B, Вердикт: OK, Время: 315ms, Память: 24.62Mb
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int ll
using ll = long long;
using vl = std::vector<ll>;
using vi = std::vector<int>;
using tiii = std::tuple<int,int,int>;
using pii = std::pair<int,int>;
using vtiii = std::vector<tiii>;
using vvi = std::vector<vi>;
const int mod = (int)1e9+7;
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
int binpow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = mul(r, a);
        a = mul(a, a);
        n >>= 1;
    }
    return r;
}
int inv(int a) {
    return binpow(a, mod-2);
}
// джедайское дерево отрезков без отложенных операций (без ленивых апдейтов)
// значение в листе считается как произведение значений от корня до листа
// запросы:
// 1) get(p) -> получить значение по индексу p
// 2) update(l, r, x) -> умножить все значения на отрезке [l, r] на x
struct SegTree {
    int n;
    vi tree;
    SegTree(int n_, int x_) : n(n_), tree(4 * n_, x_) { }
    void update(int v, int tl, int tr, int ql, int qr, int x)
    {
        if (qr <= tl || tr <= ql)
            return;
        if (ql <= tl && tr <= qr) {
            assert(0 <= v && v < isz(tree));
            tree[v] = mul(tree[v], x);
            return;
        }
        assert(tl+1<tr);
        int tm = (tl + tr) / 2;
        update(2*v+1,tl,tm,ql,qr,x);
        update(2*v+2,tm,tr,ql,qr,x);
    }
    void update(int L, int R, int x) {
        update(0, 0, n, L, R+1, x);
    }
    int get(int v, int tl, int tr, int p) const {
        if (p < tl || p >= tr)
            return 1;
        if (tl+1==tr) {
            assert(0 <= v && v < isz(tree));
            return tree[v];
        }
        assert(tl + 1 < tr);
        int tm = (tl + tr) / 2;
        if (p < tm) {
            assert(0 <= v && v < isz(tree));
            return mul(tree[v], get(2*v+1, tl, tm, p));
        } else {
            assert(p < tr);
            assert(0 <= v && v < isz(tree));
            return mul(tree[v], get(2*v+2, tm, tr, p));
        }
    }
    int get(int p) const {
        return get(0, 0, n, p);
    }
};
void solve() {
    // читаем рёбра и строим списки смежности:
    int n; std::cin >> n;
    vtiii edges(n-1);
    vvi adj(1+n);
    for (int i = 0; auto &[u, v, w] : edges) {
        std::cin >> u >> v >> w;
        adj[u].push_back(i);
        adj[v].push_back(i);
        i++;
    }
    // вспомогательные функции по работе с весами рёбер и их концами:
    auto getNextVert = [&](int edgeId, int curr) {
        assert(0 <= edgeId && edgeId < isz(edges));
        auto [u, v, _] = edges[edgeId];
        return u + v - curr;
    };
    auto getWeight = [&](int edgeId) {
        assert(0 <= edgeId && edgeId < isz(edges));
        return std::get<2>(edges[edgeId]);
    };
    auto setWeight = [&](int edgeId, int newW) {
        assert(0 <= edgeId && edgeId < isz(edges));
        std::get<2>(edges[edgeId]) = newW;
    };
    // строим эйлеров обход, чтобы сопоставить каждому поддереву подотрезок
    // в массиве
    int timer = -1;
    vi tin(n+1), tout(n+1), parent(n+1), weightId(n+1), vertexId(n+1);
    vl sumW(n+1);
    std::function<void(int,int)> dfs = [&](int u, int p) {
        tin[u] = ++timer;
        for (int i : adj[u]) {
            int v = getNextVert(i, u);
            if (v == p)
                continue;
            parent[v] = u;
            weightId[v] = i;
            vertexId[i] = v;
            sumW[u] += getWeight(i);
            dfs(v, u);
        }
        tout[u] = timer;
    };
    dfs(1, 0); // запуск dfs
    // вспомогательные функции для запросов на отрезках:
    auto getProb = [&](int edgeId) {
        int child = vertexId[edgeId];
        int par = parent[child];
        ll q = sumW[par];
        int p = getWeight(edgeId);
        return mul(p, inv(q % mod));
    };
    auto getSegment = [&](int edgeId) -> pii {
        int curr = vertexId[edgeId];
        return {tin[curr], tout[curr]};
    };
    // строим дерево отрезков + инициализируем изначальными вероятностями:
    SegTree st(n, 1);
    for (int i = 0; i < n-1; i++) {
        auto [L, R] = getSegment(i);
        st.update(L, R, getProb(i));
    }
    // обрабатываем запросы:
    int q; std::cin >> q;
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int id, w;
            std::cin >> id >> w;
            id--;
            // обновляется не только вероятность в поддереве v,
            // но и вероятность во всём поддереве его предка p,
            // потому что меняется знаменатель, равный sumW[p]
            int v = vertexId[id];
            int lv = tin[v], rv = tout[v];
            int p = parent[v];
            int lp = tin[p], rp = tout[p];
            assert(lp <= lv && rv <= rp);
            // Важно: позиция lp соответствует вершине p и её не трогать!!!
            // Отрезки [lp+1, lv-1], [lv, rv] и [rv+1, rp]:
            // 1) умножаются на oldSumWp
            // 2) делятся на newSumWp
            // Отрезок [lv, rv]:
            // 1) делится на oldWv
            // 2) умножается на newWv
            int oldSumWp = sumW[p] % mod;
            int oldWv = getWeight(id);
            setWeight(id, w);
            int newWv = getWeight(id);
            sumW[p] -= oldWv;
            sumW[p] += newWv;
            int newSumWp = sumW[p] % mod;
            st.update(lp+1, rp, mul(oldSumWp, inv(newSumWp)));
            st.update(lv, rv, mul(newWv, inv(oldWv)));
        } else {
            int u; std::cin >> u;
            int pos = tin[u];
            std::cout << st.get(pos) << "\n";
        }
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0)
        solve();
}