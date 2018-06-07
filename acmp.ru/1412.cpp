#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int n; scanf("%d", &n);
    std::vector<std::vector<int>> dist(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        char buf[101];
        scanf("%100s", buf);
        for (int j = 0; j < n; ++j) {
            dist[i][j] = (buf[j] == '1');
        }
        dist[i][i] = 1;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] && dist[k][j]) {
                    dist[i][j] = 1;
                }
            }
        }
    }
    std::vector<bool> used(n, false);
    int count = 0;
    while (true) {
        int nUsed = 0;
        for (int i = 0; i < n; ++i) {
            nUsed += used[i];
        }
        if (nUsed == n) {
            break;
        }
        std::vector<int> rank(n, 0);
        for (int vert = 0; vert < n; ++vert) {
            if (!used[vert]) {
                for (int i = 0; i < n; ++i) {
                    if (dist[i][vert]) {
                        ++rank[i];
                    }
                }
            }
        }
        int v = (int)(std::max_element(rank.begin(), rank.end())-rank.begin());
        for (int j = 0; j < n; ++j) {
            if (dist[v][j]) {
                used[j] = true;
            }
        }
        ++count;
    }
    printf("%d", count);
    return 0;
}