#include <stdio.h>
#include <algorithm>
#include <vector>

struct Edge {
    int a, b, cost;
    
    static Edge read() {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        return Edge{a,b,c};
    }
};

int main() {
    int nVert, nEdges;
    scanf("%d %d", &nVert, &nEdges);
    
    std::vector<Edge> edges;
    for (int i = 0; i < nEdges; ++i) {
        edges.push_back(Edge::read());
    }
    
    const int INF = 30000;
    
    std::vector<int> dist(1+nVert, INF); 
    dist[1] = 0;
    
    for (int d = 1; d < nVert; ++d) {
        for (const auto& e : edges) {
            if (dist[e.a] < INF) {
                dist[e.b] = std::min(dist[e.b], dist[e.a] + e.cost);
            }
        }
    }
    
    for (int v = 1; v <= nVert; ++v) {
        printf("%d ", dist[v]);
    }
    
    return 0;
}