#include <bits/stdc++.h>

struct Pair {
    int rang, pos;
};

int main() {
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(0); std::cout.tie(0);
    
    int nVert, nEdges; 
    std::cin >> nVert >> nEdges;
    
    std::vector<Pair> pairs;
    for (int i = 0; i < nVert; ++i) { 
        int rang; 
        std::cin >> rang; 
        pairs.push_back({rang, i}); 
    }
    
    std::sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) { 
        return a.rang > b.rang || (a.rang == b.rang && a.pos < b.pos);
    });
    
    std::vector<int> old_pos(nVert), new_pos(nVert);
    for (int i = 0; i < nVert; ++i) {
        const auto& it = pairs[i];
        old_pos[i] = it.pos;
        new_pos[it.pos] = i;
    }
    
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < nEdges; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges.push_back({new_pos[a], new_pos[b]});
        edges.push_back({new_pos[b], new_pos[a]});
    }
    std::sort(edges.begin(), edges.end());
    edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
    
    std::vector<int> answer(nVert);
    for (int i = 0, r = 0; i+1 < nVert; ++i) {
        while (r < nVert && pairs[r].rang == pairs[i].rang) ++r;
        auto low = std::lower_bound(edges.begin(), edges.end(), std::make_pair(i, r));
        auto high = std::lower_bound(low, edges.end(), std::make_pair(i, nVert));
        answer[old_pos[i]] = std::max(0, nVert - r - int(high-low));
    }
    for (auto& it : answer) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    return 0;
}