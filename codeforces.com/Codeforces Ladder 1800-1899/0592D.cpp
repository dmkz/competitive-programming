/*
    Problem: 592D. Super M
    Solution: trees, dfs, bfs, diameter of tree, O(n)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
const int INF = (int)1e9+7;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int nVert, nAttack; std::cin >> nVert >> nAttack; ) {
        std::vector<std::set<int>> adj(1+nVert);
        int nEdges = nVert - 1;
        for (int i = 0, u, v; i < nEdges; i++) {
            std::cin >> u >> v;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        vi attack(nAttack);
        for (auto & it : attack) std::cin >> it;
        std::sort(all(attack));
        // BFS:
        std::function<vi(int)> bfs = [&](int s) {
            vi dist(1+nVert, INF);
            dist[s] = 0;
            std::queue<int> queue; queue.push(s);
            while (isz(queue)) {
                auto curr = queue.front(); queue.pop();
                for (int next : adj[curr]) {
                    if (dist[next] == INF) {
                        dist[next] = dist[curr] + 1;
                        queue.push(next);
                    }
                }
            }
            return dist;
        };
        auto findMaxFrom = [&](int from, const vi& dist) {
            int max = from;
            for (int v : attack) {
                if (dist[v] > dist[max] || (dist[v] == dist[max] && v < max)) {
                    max = v;
                }
            }
            return max;
        };
        vi dist = bfs(attack.front());
        int max = findMaxFrom(attack.front(), dist);
        dist = bfs(max);
        int root = findMaxFrom(max, dist);
        std::function<void(int,int)> dfs = [&](int u, int p) {
            int nBranches = 0;
            for (auto it = adj[u].begin(); it != adj[u].end(); ) {
                auto next = std::next(it);
                if (*it == p) {
                    it = next;
                    continue;
                }
                int v = *it;
                dfs(v, u);
                if (isz(adj[v])) {
                    it++;
                    nBranches++;
                } else {
                    it = next;
                }
            }
            if (nBranches == 0 && std::binary_search(all(attack), u) == false) {
                adj[u].erase(p);
                adj[p].erase(u);
                nEdges--;
            }
        };
        dfs(root, -1);
        dist = bfs(root);
        int s = findMaxFrom(root, dist);
        std::cout << std::min(s,root) << '\n' << nEdges * 2 - dist[s] << std::endl;
    }
    return 0;
}