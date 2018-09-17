/*
    Задача: 1389. Печатная схема
    
    Решение: DSU, алгоритм Краскала, минимальное остовное дерево, O(n * m * log(n * m))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge { int u, v, cost; };

bool operator<(const Edge& a, const Edge& b) {
    if (a.cost < b.cost) return true;
    if (a.cost > b.cost) return false;
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}

struct DSU {
    std::vector<int> parent, size;
    DSU(int n) : parent(1+n), size(1+n,1) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int get_parent(int u) {
        return parent[u] == u ? u : parent[u] = get_parent(parent[u]);
    }
    void union_sets(int u, int v) {
        u = get_parent(u), v = get_parent(v);
        if (u != v) {
            if (size[u] < size[v]) std::swap(u,v);
            size[u] += size[v];
            parent[v] = u;
        }
    }
};

void int2pos(int number, int& r, int& c, int nRows, int nCols) {
    assert(1 <= number && number <= nRows * nCols);
    r = (number+nCols-1) / nCols;
    c = number - (r-1) * nCols;
    assert(1 <= r && r <= nRows);
    assert(1 <= c && c <= nCols);
    assert(number == (r-1) * nCols + c);
}

void pos2int(int& number, int r, int c, int nRows, int nCols) {
    assert(1 <= r && r <= nRows);
    assert(1 <= c && c <= nCols);
    number = (r-1) * nCols + c;
    assert(1 <= number && number <= nRows * nCols);
    assert(r == (number+nCols-1) / nCols);
    assert(c == number - (r-1) * nCols);
}

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    DSU dsu(nRows*nCols);
    std::vector<Edge> edges;
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            int u, val; pos2int(u,r,c,nRows,nCols);
            scanf("%d", &val);
            if ((val >> 0) & 1) {
                assert(r+1 <= nRows);
                int v; pos2int(v,r+1,c,nRows,nCols);
                dsu.union_sets(u,v);
            }
            if ((val >> 1) & 1) {
                assert(c+1 <= nCols);
                int v; pos2int(v,r,c+1,nRows,nCols);
                dsu.union_sets(u,v);
            }
            if (r+1 <= nRows) {
                int v; pos2int(v,r+1,c,nRows,nCols);
                edges.push_back(Edge{u,v,1});
            }
            if (c+1 <= nCols) {
                int v; pos2int(v,r,c+1,nRows,nCols);
                edges.push_back(Edge{u,v,2});
            }
        }
    }
    std::sort(edges.begin(), edges.end());
    int sum = 0; std::vector<Edge> answ;
    for (auto& e : edges) {
        int pu = dsu.get_parent(e.u), pv = dsu.get_parent(e.v);
        if (pu != pv) {
            sum += e.cost;
            answ.push_back(e);
            dsu.union_sets(e.u,e.v);
        }
    }
    printf("%d %d\n", (int)answ.size(), sum);
    for (auto& e : answ) {
        int r1, c1; int2pos(e.u,r1,c1,nRows,nCols);
        int r2, c2; int2pos(e.v,r2,c2,nRows,nCols);
        printf("%d %d", r1, c1);
        if (c2 != c1) printf(" 2\n");
        if (r2 != r1) printf(" 1\n");
    }
    return 0;
}