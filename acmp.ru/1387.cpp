/*
    Задача: 1387. Остовное дерево
    
    Решение: графы, алгоритм Краскала, DSU, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

typedef long long ll;

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
    DSU(int n) : parent(1+n,0), size(1+n,1) {
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int get_parent(int a) {
        return parent[a] == a ? a : parent[a] = get_parent(parent[a]);
    }
    void union_sets(int a, int b) {
        a = get_parent(a), b = get_parent(b);
        if (b != a) {
            if (size[a] < size[b]) std::swap(a,b);
            size[a] += size[b];
            parent[b] = a;
        }
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    DSU dsu(1+n);
    std::vector<Edge> edges(m);
    for (auto& e : edges) {
        scanf("%d %d %d", &e.u, &e.v, &e.cost);
    }
    std::sort(edges.begin(), edges.end());
    ll answ = 0;
    for (auto& e : edges) {
        int pu = dsu.get_parent(e.u), pv = dsu.get_parent(e.v);
        if (pu != pv) {
            answ += e.cost;
            dsu.union_sets(e.u,e.v);
        }
    }
    std::cout << answ;
    return 0;
}