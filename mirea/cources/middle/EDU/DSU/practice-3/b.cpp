#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vi = std::vector<int>;
using tiii = std::tuple<int,int,int>;
using vtiii = std::vector<tiii>;

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
    
    void connect(pii pair) {
        connect(pair.first, pair.second);
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

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем число вершин и число рёбер:
    int nV, nE; std::cin >> nV >> nE;
    // читаем сами рёбра:
    vpii edges(nE);
    for (auto &[u,v] : edges)
        std::cin >> u >> v;
    // читаем запросы как тройки чисел (L, R, номер запроса):
    // и сортируем их компаратором Мо
    const int gsize = std::max<int>(1, (int)std::sqrt(nE));
    int nQ; std::cin >> nQ;
    vi answer(nQ);
    std::vector<vtiii> queries((nE + gsize - 1) / gsize);
    for (int id = 0; id < nQ; id++) {
        int L, R;
        std::cin >> L >> R;
        L--, R--; // в ноль индесакцию идём
        int idBlockL = L / gsize;
        int idBlockR = R / gsize;
        // если отрезок целиком лежит внутри блока, то сразу на него
        // ответим за O(gsize)
        if (idBlockL == idBlockR) {
            DSU dsu(nV);
            for (int i = L; i <= R; i++)
                dsu.connect(edges[i]);
            answer[id] = dsu.numSets;
            continue;
        }
        // иначе запомним что на него надо ответить!
        queries[idBlockL].emplace_back(L, R, id);
    }
    
    for (auto &block : queries)
        std::sort(all(block), [&](const tiii & a, const tiii & b)
        {
            auto [aL, aR, aId] = a;
            auto [bL, bR, bId] = b;
            // по возрастанию правой границы
            return aR < bR;
        });
    // отвечаем на запросы
    for (const auto &block : queries) {
        if (block.empty())
            continue;
        //std::cout << std::string(40, '-') << std::endl;
        //std::cout << "new block!" << std::endl;
        // внутри блока правая граница только увеличивается
        // а левая колеблется в пределах этого блока
        // построим dsu для первого запроса, а дальше будем откатывать
        // по левой границе
        
        // найдём максимальный L и построим DSU на отвезке [maxL, minR]
        int minR = std::get<1>(block.front());
        int maxL = INT_MIN;
        for (const auto &[L, R, id] : block)
            maxL = std::max(maxL, L);
        assert(maxL <= minR);
        DSU dsu(nV);
        for (int i = maxL; i <= minR; i++)
            dsu.connect(edges[i]);
        // отвечаем на запросы:
        int currL = maxL, currR = minR;
        for (const auto &[L, R, id] : block)
        {
            //std::cout << "L=" << L << ", R=" << R << ", id=" << id << std::endl;
            // инвариант: текущее L всегда равно максимальному L
            // (до обработки запроса)
            assert(currL == maxL);
            while (currR < R) // добавляем новые рёбра справа
                dsu.connect(edges[++currR]);
            assert(R == currR);
            assert(currL <= currR);
            // запоминаем текущую версию:
            int lastVersion = dsu.getVersion();
            // накидываем рёбра слева
            while (L < currL)
                dsu.connect(edges[--currL]);
            // проверим что сформировали dsu под наш запрос:
            assert(currL == L && currR == R);
            // отвечаем на запрос:
            answer[id] = dsu.numSets;
            // откатываем изменения к максимальному L
            dsu.rollBack(lastVersion);
            currL = maxL;
        }
    }
    // выводим ответы:
    for (auto it : answer)
        std::cout << it << '\n';
}
