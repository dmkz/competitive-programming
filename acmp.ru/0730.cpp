/*
    "Пересылка файлов": графы, рекурсивный перебор, сочетания, O(C(m,n-1)*m)
*/

#include <stdio.h>
#include <vector>
#include <queue>

const int INF = (int)1e9;
 
struct Edge {
    int u, v, cost;
} edges[30];

int answ = INF, vect, used = 0;

int nVert, nEdges;

std::vector<int> g[30];

void go(const int id, const int need, const int sum) {
    if (need == 0) {
        std::vector<bool> visited(1+nVert, false);
        visited[1] = true;
        int nVisited = 1;
        std::queue<int> queue;
        queue.push(1);
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            for (auto next : g[curr]) {
                if (!visited[next]) {
                    visited[next] = true;
                    ++nVisited;
                    if (!g[next].empty()) {
                        queue.push(next);
                    }
                }
            }
        }
        if (nVisited == nVert && sum < answ) {
            vect = used;
            answ = sum;
        }
        return;
    }
    // берем если need > 0
    if (need > 0) {
        const int u = edges[id].u;
        const int v = edges[id].v;
        used |= (1 << id);
        g[u].push_back(v);
        go(id+1, need-1, sum + edges[id].cost);
        g[u].pop_back();
        used &= ~(1 << id);
    }
    if (nEdges - id > need) {
        go(id+1, need, sum);
    }
}
 
int main() {
    scanf("%d %d", &nVert, &nEdges);
    if (nVert == 1) {
        printf("0 0");
        return 0;
    }
    
    for (int i = 0; i < nEdges; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
    }
    
    go(0, nVert-1, 0);
    
    std::vector<int> vector;
    for (int i = 0; i < nEdges; ++i) {
        if ((vect >> i) & 1) {
            vector.push_back(i+1);
        }
    }
    
    printf("%d %d\n", answ, (int)vector.size());
    for (auto& it : vector) {
        printf("%d ", it);
    }
    return 0;
}