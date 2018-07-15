/*
    "Слабая K-связность": алгоритм Флойла-Уоршелла, O(n^3)
*/

#include <stdio.h>
#include <vector>
#include <cassert>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);
    
    const int INF = (int)1e9;
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    
    int m;
    scanf("%d", &m);
    
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        dist[a][b] = 0;
        dist[b][a] = std::min(dist[b][a], 1);
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    
    int answ = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            answ = std::max(answ, dist[i][j]);
        }
    }
    printf("%d", answ);
    return 0;
}