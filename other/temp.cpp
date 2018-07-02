#include <iostream>
#include <vector>

struct Edge {
    int v, cost;
};

struct Tree {
    
    int nVert, root;
    
    std::vector<std::vector<Edge>> edges;
    
    std::vector<int> parent, size;
    
    Tree(int nVert, int root) : nVert(nVert), root(root) {
        edges.resize(nVert);
        parent.assign(nVert, -1);
        size.assign(nVert, 0);
    }
    
    void add_edge(const int u, const int v, const int cost) {       
        edges[u].push_back(Edge{v, cost});
        edges[v].push_back(Edge{u, cost});
    }
    
    int calc_size(int u) {
        if (size[u] == 0) {
            size[u] = 1;
            for (auto& e : edges[u]) {
                if (e.v != parent[u]) {
                    parent[e.v] = u;
                    size[u] += calc_size(v);
                }
            }
        }
        return size[u];
    }
};

struct HeavyLight {
    
    Tree& t;
    
    std::vector<std::vector<int>> path;
    
    std::vector<int> id, position;
    
    build(
    
    HeavyLight(Tree& t) : t(t) {
        id.assign(t.nVert, -1);
        position.assign(t.nVert, -1);

        build(t.root, 0);
    }
    
    
    
    
};



int main() {
    
    
    
    return 0;
}