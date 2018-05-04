#pragma GCC diagnostic ignored "-Wunused-result"

#include <stdio.h>
#include <bits/stdc++.h>

struct Edge {
    int vert, start, finish;
};

bool operator<(const Edge& a, const Edge& b) {
    return a.finish < b.finish || (a.finish == b.finish && (a.start < b.start || (a.start == b.start && a.vert < b.vert)));
}
                                   
bool operator>(const Edge& a, const Edge& b) {
    return b < a;
}

int main() {
    int nVert, finish, nPaths; 
    scanf("%d %d %d", &nVert, &finish, &nPaths); 
    --finish;
    
    std::vector<std::vector<Edge>> edges(nVert);
    for (int i = 0; i < nPaths; ++i) {
        int k; scanf("%d", &k);
        int prev_vert, prev_time, curr_vert, curr_time = -1;
        for (int j = 0; j < k; ++j) {
            int v, t; scanf("%d %d", &v, &t); --v;
            prev_vert = curr_vert;
            prev_time = curr_time;
            curr_vert = v;
            curr_time = t;
            if (prev_time != -1) {
                edges[prev_vert].push_back(Edge{curr_vert, prev_time, curr_time});
            }
        }
    }
    
    for (auto& v : edges) std::sort(v.begin(), v.end());
    
    const int INF = (int)1e9+1;
    std::vector<int> dist(nVert, INF);
    dist[0] = 0;
    
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue; 
    queue.push(Edge{0, 0, 0});
    
    while (!queue.empty()) {
        auto curr = queue.top(); queue.pop();
        assert(dist[curr.vert] < INF);
        if (curr.vert == finish || curr.finish == INF) break;
        for (auto& next : edges[curr.vert]) {
            if (curr.finish > next.start) continue;
            if (next.finish < dist[next.vert]) {
                dist[next.vert] = next.finish;
                queue.push(Edge{next.vert, 0, next.finish});
            }
        }
    }
    printf("%d\n", dist[finish] == INF ? -1 : dist[finish]);
    return 0;
}