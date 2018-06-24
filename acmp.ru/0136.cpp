#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int n;
    scanf("%d", &n);
    std::vector<std::vector<int>> d(n, std::vector<int>(n));
    const int INF = (int)1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value; scanf("%d", &value);
            if (value == -1) value = INF;
            d[i][j] = value;
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF) {
                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    int i_max = -1, j_max = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][j] != INF && (i_max == -1 || d[i][j] > d[i_max][j_max])) {
                i_max = i;
                j_max = j;
            }
        }
    }
    assert(i_max != -1);
    printf("%d", d[i_max][j_max]);
    return 0;
}