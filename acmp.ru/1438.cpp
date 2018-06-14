#include <stdio.h>
#include <algorithm>
#include <vector>

struct DSU {
    // Система непересекающихся множеств: size - размер множества, parent - представитель множества
    std::vector<int> size, parent;
    // Конструктор для множества фиксированного размера:
    DSU(const int size) : size(size, 0), parent(size, -1) { }
    // Добавление новой вершины в множество:
    void make_set(const int v) {
        parent[v] = v;
        size[v] = 1;
    }
    // Нахождение представителя множества, к которому относится вершина v:
    int find_set(const int v) {
        return v == parent[v] ? v : parent[v] = find_set(parent[v]);
    }
    // Нахождение размера множества для вершины v:
    int get_size(const int v) {
        return size.at(find_set(v));
    }
    // Объединение множеств для вершин a и b:
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                std::swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

struct Edge {
    int a, b, cost;
};

int main() {    
    int nVert, nEdges, size;
    scanf("%d %d %d", &nVert, &nEdges, &size);

    std::vector<Edge> edges;
    for (int i = 0; i < nEdges; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a, --b;
        edges.push_back(Edge{a,b,c});
        edges.push_back(Edge{b,a,c});
    }
    // Отсортируем ребра в порядке невозрастания их длин:
    std::stable_sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r){
        return l.cost > r.cost;
    });
    // Будем поддерживать размер текущих компонент связностей в системе непересекающихся множеств:
    DSU dsu(nVert);
    // Изначально занесем каждую вершину в dsu:
    for (int v = 0; v < nVert; ++v) {
        dsu.make_set(v);
    }
    // Будем добавлять текущее ребро, жадно объединяя множества для вершин, которые оно соединяет:
    for (auto& e : edges) {
        dsu.union_sets(e.a, e.b);
        if (dsu.get_size(e.a) > size) {
            printf("%d\n", e.cost);
            return 0;
        }
    }
    
    throw 1;
}