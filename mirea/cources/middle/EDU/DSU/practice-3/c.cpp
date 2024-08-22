#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
struct DSU {
    
    std::vector<int> sz, par;
    
    int numSets;
    
    std::vector<std::pair<int *, int>> history;
    
    DSU(int n = 0)
        : sz(n+1, 1)
        , par(n+1)
        , numSets(n)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    bool isConnected(int u, int v) const {
        return getPar(u) == getPar(v);
    }
    
    int getPar(int u) const {
        return (u == par[u] ? u : getPar(par[u]));
    }
    
    void addToHistory(int *pointer) {
        history.emplace_back(pointer, *pointer);
    }
    
    int getVersion() const {
        return (int)history.size();
    }
    
    void rollBack(int version) {
        while ((int)history.size() > version) {
            auto [pointer, value] = history.back();
            history.pop_back();
            *pointer = value;
        }
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        // запомнить изменённые значения:
        addToHistory(&sz[u]);
        addToHistory(&par[v]);
        addToHistory(&numSets);
        // присоединять "v" к "u"
        sz[u] += sz[v];
        par[v] = u;
        numSets--;
    }
    
};

using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;

DSU dsu;
vi queries;
vvpii edges;

void assign(int nVertices, int nTimeMoments) {
    queries.assign(4*nTimeMoments, -1);
    edges.assign(4*nTimeMoments, vpii{});
    dsu = DSU(nVertices); // 1-индексакция
}

void insertAskQuery(int v, int tl, int tr, int i, int id) {
    if (i < tl || i >= tr)
        return;
    if (tl + 1 == tr) {
        queries[v] = id;
        return;
    }
    int tm = (tl+tr)/2;
    insertAskQuery(2*v+1, tl, tm, i, id);
    insertAskQuery(2*v+2, tm, tr, i, id);
}

void insertEdge(int v, int tl, int tr,
                int ql, int qr, int a, int b)
{
    if (tr <= ql || qr <= tl)
        return; // пересечений нет
    if (ql <= tl && tr <= qr) {
        // целиком входит
        edges[v].emplace_back(a, b);
        return;
    }
    int tm = (tl+tr)/2;
    insertEdge(2*v+1,tl,tm,ql,qr,a,b);
    insertEdge(2*v+2,tm,tr,ql,qr,a,b);
}

void solve(int v, int tl, int tr, vi &answers) {
    assert(tl < tr); // убедилить что пришли в валидный узел
    // добавить в DSU все рёбра которые лежат в этом узле
    const int lastVersion = dsu.getVersion();
    for (const auto &[a, b] : edges[v])
        dsu.connect(a, b);
    if (tl + 1 == tr)
    {
        // пришли в лист, надо ответить на запрос
        int idQuery = queries[v];
        if (idQuery != -1) {
            // есть запрос
            answers[idQuery] = dsu.numSets;
        }
    } else {        
        int tm = (tl + tr) / 2;
        solve(2*v+1, tl, tm, answers); // идём влево
        solve(2*v+2, tm, tr, answers); // идём вправо
    }
    // откатим при возвращении наверх:
    dsu.rollBack(lastVersion);
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    if (q == 0)
        return 0;
    assign(n, q); // инициализируем дерево отрезков и dsu
    int nAskQueries = 0;
    std::map<pii, int> left;
    std::set<pii> opened; // какие рёбра прямо сейчас открыты?
    for (int i = 0; i < q; i++) {
        char t; std::cin >> t;
        if (t == '?') {
            insertAskQuery(0, 0, q, i, nAskQueries++);
        } else {
            int u, v; std::cin >> u >> v;
            if (u > v) std::swap(u, v);
            if (t == '+') {
                // отрезок открывается
                left[{u,v}] = i;
                opened.insert({u,v});
            } else {
                assert(t == '-');
                // отрезок закрывается
                opened.erase({u,v});
                insertEdge(0, 0, q, left[{u,v}], i, u, v);
            }
        }
    }
    // добавляем все рёбра которые ещё не закрыты:
    for (const auto &[u, v] : opened)
        insertEdge(0, 0, q, left[{u,v}], q, u, v);
    // вызываем рекурсивную функцию, которая обойдёт всё дерево,
    // и ответит на все запросы
    vi answers(nAskQueries);
    solve(0, 0, q, answers);
    // выведем эти ответы:
    for (auto it : answers)
        std::cout << it << '\n';
}
