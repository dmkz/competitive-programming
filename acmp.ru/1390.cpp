/*
    Задача: 1390. Маршрут для гонца
    
    Решение: графы, Эйлеров обход, поиск в глубину, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge {
    int u, v, id;
    
    Edge(int u_ = 0, int v_ = 0, int id_ = 0)
        : u(u_), v(v_), id(id_) { }
};

int main() {
    // Читаем ребра:
    int n, nAdded = 0; scanf("%d", &n);
    std::vector<Edge> edges;
    for (int i = 0; i < 2*n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        int s = (u+3) / 4, t = (v+3) / 4;
        assert(s != t);
        ++nAdded;
        int mid = n + nAdded;
        // Добавим новую вершину `mid` между вершинами `s` и `t`
        // Ребро `s` -- `mid` будет иметь идентификатор `u`
        // Ребро `t` -- `mid` будет иметь идентификатор `v`
        edges.push_back(Edge(s, mid, u));
        edges.push_back(Edge(t, mid, v));
    }
    // Создаем списки смежности и считаем валентности вершин:
    std::vector<int> nEdges(1+n+nAdded);
    std::vector<std::vector<int>> next(1+n+nAdded);
    for (int i = 0; i < (int)edges.size(); ++i) {
        const auto& e = edges[i];
        next[e.u].push_back(i); nEdges[e.u]++;
        next[e.v].push_back(i); nEdges[e.v]++;
    }
    // Эйлеров обход графа в глубину:
    std::vector<int> stack{1}, stackEdges, answ;
    while (!stack.empty()) {
        auto curr = stack.back();
        while (true) {
            if (next[curr].empty()) {
                if (!stackEdges.empty()) {
                    answ.push_back(stackEdges.back());
                    stackEdges.pop_back();
                }
                stack.pop_back();
                break;
            }
            int e = next[curr].back();
            if (edges[e].id == 0) {
                next[curr].pop_back();
                continue;
            }
            // Удаление ребра `e` и переход в следующую вершину:
            assert(nEdges[curr] > 0);
            nEdges[curr]--;
            curr = edges[e].u + edges[e].v - curr;
            assert(nEdges[curr] > 0);
            nEdges[curr]--;
            stackEdges.push_back(edges[e].id);
            edges[e].id = 0;
            stack.push_back(curr);
        }
    }
    if ((int)answ.size() != 4 * n) {
        printf("No\n"); 
        return 0; 
    }
    printf("Yes\n");
    for (auto& it : answ) printf("%d ", it);
    return 0;
}