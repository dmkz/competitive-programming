/*
    Solution: Trees, Constructive, O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int a, b;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert, diam, degree, n;
    std::cin >> nVert >> diam >> degree;
    
    if (diam > nVert-1) {
        std::cout << "NO";
        return 0;
    }
    
    std::vector<Edge> edges;
    
    std::vector<int> deg(1+nVert, 0), dist(1+nVert, 0);

    // Construct chain 1-2-3-4-5-...-diam-(diam+1)
    for (n = 1; n <= diam; ++n) {
        edges.push_back(Edge{n, n+1});
        deg[n]++; deg[n+1]++;
    }
    // Calculate max distance to vertex in chain from other vertices:
    for (int l = 1, r = n, len = diam; l <= r; ++l, --r, --len) {
        dist[l] = dist[r] = len;
    }
    // Just iterate over added vertices and add new:
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == diam) {
            continue;
        }
        while (n < nVert && deg[i] < degree) {
            edges.push_back(Edge{i, n+1});
            deg[i]++; deg[n+1]++;
            dist[n+1] = dist[i]+1;
            ++n;
        }
    }
    // Check answer:
    if (n < nVert || *std::max_element(deg.begin()+1, deg.end()) > degree) {
        std::cout << "NO";
        return 0;
    }
    // Output:
    std::cout << "YES\n";
    for (auto& it : edges) {
        std::cout << it.a << ' ' << it.b << '\n';
    }
    
    return 0;
}