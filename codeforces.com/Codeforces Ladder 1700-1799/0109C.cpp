/*
    Problem: 109C. Lucky Tree
    
    Solution: trees, bfs, combinatorics, connected components, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
bool is_lucky_number(int x) {
    do {
        int d = x % 10;
        if (!(d == 7 || d == 4)) {
            return false;
        }
        x /= 10;
    } while (x > 0);
    return true;
}
struct Edge {
    int u, v;
    bool t;
};
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<Edge> edges;
        vvi adj(n+1);
        for (int i = 1, u, v, w; i < n; i++) {
            std::cin >> u >> v >> w;
            edges.push_back(Edge{u,v,is_lucky_number(w)});
            adj[u].push_back(isz(edges)-1);
            adj[v].push_back(isz(edges)-1);
        }
        vi part(1+n);
        int nParts = 0;
        for (int u = 1; u <= n; u++) {
            if (!part[u]) {
                ++nParts;
                std::queue<int> queue;
                queue.push(u);
                while (!queue.empty()) {
                    auto curr = queue.front(); queue.pop();
                    for (int eid : adj[curr]) {
                        if (edges[eid].t == 0) {
                            int next = edges[eid].u + edges[eid].v - curr;
                            if (!part[next]) {
                                part[next] = nParts;
                                queue.push(next);
                            }
                        }
                    }
                }
            }
        }
        vi partSize(nParts+1);
        for (int u = 1; u <= n; u++) {
            partSize[part[u]]++;
        }
        ll answ = n * (n-1LL) * (n-2LL);
        for (int idPart = 1; idPart <= nParts; ++idPart) {
            auto ps = partSize[idPart];
            answ -= ps * (ps - 1LL) * (ps - 2LL);
            answ -= 2 * ps * (ps - 1LL) * (n - ps);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}