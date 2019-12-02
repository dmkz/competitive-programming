/*
    Problem: 449B. Jzzhu and Cities
    Solution: graphs, dijkstra's algorithm, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
const auto io_sync_off = [](){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    return 0;
}();
using ll = long long;
struct Edge {
    int to; ll cost; bool additional;
};
using ve = std::vector<Edge>;
using vl = std::vector<ll>;
using vve = std::vector<ve>;
const ll INF = (ll)1e18L;
bool operator<(const Edge& a, const Edge& b) {
    if (a.cost < b.cost) return true;
    if (a.cost > b.cost) return false;
    return a.additional < b.additional || (a.additional == b.additional && a.to < b.to);
}
template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
int main() {
    int nVert, nEdges, nAdd;
    while (std::cin >> nVert >> nEdges >> nAdd) {
        vve edges(1+nVert);
        for (int i = 0; i < nEdges; i++) {
            int u, v, c;
            std::cin >> u >> v >> c;
            edges[u].push_back(Edge{v,c,false});
            edges[v].push_back(Edge{u,c,false});
        }
        vl dist(1+nVert, INF), visited(1+nVert);
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
        queue.push(Edge{1, 0, false});
        int answ = 0;
        for (int i = 0; i < nAdd; i++) {
            int v, x; std::cin >> v >> x;
            queue.push(Edge{v,x,true});
        }
        while (isz(queue)) {
            auto st = queue.top();
            queue.pop();
            if (visited[st.to]) {
                answ += st.additional;
                continue;
            }
            assert(dist[st.to] >= st.cost);
            visited[st.to] = true;
            dist[st.to] = st.cost;
            for (auto &e : edges[st.to]) {
                if (!visited[e.to] && dist[e.to] > e.cost + st.cost) {
                    queue.push(Edge{e.to, e.cost + st.cost, false});
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}