/*
    Задача: 1388. Школы
    
    Решение: DSU, алгоритм Краскала, Sparse Table, dfs, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

struct Edge {
    int u, v, cost;
};

bool operator<(const Edge& a, const Edge& b) {
    if (a.cost < b.cost) return true;
    if (a.cost > b.cost) return false;
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

struct DSU {
    std::vector<int> parent, size;
    DSU (int n) : parent(1+n,0), size(1+n,1) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int get_parent(int a) {
        return parent[a] == a ? a : parent[a] = get_parent(parent[a]);
    }
    void union_sets(int a, int b) {
        a = get_parent(a), b = get_parent(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a,b);
            size[a] += size[b];
            parent[b] = a;
        }
    }
};

const int INF = (int)1e9+1;

int main() {
    // Ввод ребер и их сортировка:
    int n, m; scanf("%d %d", &n, &m);
    std::vector<Edge> edges(m); std::vector<bool> used(m);
    for (auto& e : edges) {
        scanf("%d %d %d", &e.u, &e.v, &e.cost);
    }
    std::sort(edges.begin(), edges.end());
    // Построение минимального остова в виде дерева:
    DSU dsu(n);
    std::vector<std::vector<Edge>> next(1+n);
    int min1 = 0;
    for (int i = 0; i < m; ++i) {
        const auto& e = edges[i];
        int pu = dsu.get_parent(e.u), pv = dsu.get_parent(e.v);
        if (pu != pv) {
            next[e.u].push_back(e);
            next[e.v].push_back(e);
            dsu.union_sets(e.u, e.v);
            min1 += e.cost;
            used[i] = true;
        }
    }
    // Построение LCA и Sparse Table на дереве:
    const int PMAX = 10, NMAX = 512;
    static int max[PMAX][NMAX], par[PMAX][NMAX];
    std::vector<int> dep(1+n);
    std::function<void(int,int,int)> visit = [&](int u, int p, int c) {
        max[0][u] = c;
        par[0][u] = p;
        dep[u] = dep[p]+1;
        for (auto& e : next[u]) {
            int v = e.u + e.v - u;
            if (v == p) continue;
            visit(v,u,e.cost);
        }
    };
    visit(1,0,0);
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 1; i <= n; ++i) {
            int j = par[p-1][i];
            par[p][i] = par[p-1][j];
            max[p][i] = std::max(max[p-1][i], max[p-1][j]);
        }
    }
    // Функция получения ответа: вес максимального ребра на пути от `u` до `v`
    std::function<int(int,int)> get_max = [&](int u, int v) {
        if (dep[u] > dep[v]) std::swap(u,v);
        int delta = dep[v] - dep[u];
        int ret = 0;
        for (int p = PMAX-1; p >= 0; --p) {
            if ((delta >> p) & 1) {
                ret = std::max(ret, max[p][v]);
                v = par[p][v];
            }
        }
        for (int p = PMAX-1; p >= 0; --p) {
            int pu = par[p][u], pv = par[p][v];
            if (pu != pv) {
                ret = std::max(ret, max[p][u]);
                ret = std::max(ret, max[p][v]);
                u = pu, v = pv;
            }
        }
        if (u == v) return ret;
        ret = std::max(ret, max[0][u]);
        ret = std::max(ret, max[0][v]);
        return ret;
    };
    // Находим вес второго минимального остова:
    int min2 = INF;
    for (int i = 0; i < m; ++i) {
        if (used[i]) continue;
        const auto& e = edges[i];
        min2 = std::min(min2, min1 - get_max(e.u, e.v) + e.cost);
    }
    printf("%d %d", min1, min2);
    return 0;
}