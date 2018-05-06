#include <bits/stdc++.h>

typedef int64_t Int;

const int INF = (int)1e9+1;

int main() {
    int nVert, nEdges; std::cin >> nVert >> nEdges;
    std::vector<std::vector<int>> edges(nVert);
    for (int i = 0; i < nEdges; ++i) {
        int a, b; 
        std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    int compCount = 0;
    std::vector<int> comp(nVert, -1);
    std::vector<int> compSize;
    for (int i = 0; i < nVert; ++i) {
        if (comp[i] == -1) {
            std::function<void(int,int)> dfs = [&](const int curr, const int number) {
                for (auto& next : edges[curr]) {
                    if (comp[next] == -1) {
                        comp[next] = number;
                        compSize.back()++;
                        dfs(next, number);
                    }
                }
            };
            comp[i] = compCount;
            compSize.push_back(1);
            dfs(i, compCount++);
            //std::cout << "i = " << i << std::endl;
        }
    }
    //std::cout << "first!" << std::endl;
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < nVert; ++i) {
        pairs.push_back({comp[i], i});
    }
    std::sort(pairs.begin(), pairs.end());
    std::vector<char> isCycle(compCount, false);
    int i = 0, curr = 0;
    while (i < nVert) {
        assert(curr < compCount);
        bool flag = compSize[curr] >= 3;
        while (flag && i < nVert && pairs[i].first == curr) {
            if (edges[pairs[i].second].size() % 2 == 1) {
                flag = false;
                break;
            }
            ++i;
        }
        assert(curr < compCount);
        isCycle[curr] = flag;
        ++curr;
        while (i < nVert && pairs[i].first < curr) ++i;
    }
    std::cout << std::accumulate(isCycle.begin(), isCycle.end(), 0) << std::endl;
    return 0;
}