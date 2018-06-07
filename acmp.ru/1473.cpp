#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

int main() {
    int nVert, nEdges;
    scanf("%d %d", &nVert, &nEdges);
    std::vector<std::vector<bool>> g(nVert, std::vector<bool>(nVert));
    while (nEdges--) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        if (a != b) {
            g[a][b] = g[b][a] = true;
        }
    }
    std::vector<int> part(nVert, -1);
    int nParts;
    scanf("%d", &nParts);
    std::queue<int> queue;
    for (int i = 0; i < nParts; ++i) {
        int v; 
        scanf("%d", &v);
        --v;
        part[v] = i;
        queue.push(v);
    }
    while (!queue.empty()) {
        auto curr = queue.front(); queue.pop();
        for (int next = 0; next < nVert; ++next) {
            if (g[curr][next] && part[next] == -1) {
                part[next] = part[curr];
                queue.push(next);
            }
        }
    }
    std::vector<std::vector<int>> answ(nParts);
    for (int v = 0; v < nVert; ++v) {
        assert(part[v] != -1);
        answ[part[v]].push_back(v+1);
    }
    for (const auto& part : answ) {
        assert(!part.empty());
        printf("%d\n", (int)part.size());
        for (const auto& it : part) {
            printf("%d ", it);
        }
        printf("\n");
    }
    return 0;
}