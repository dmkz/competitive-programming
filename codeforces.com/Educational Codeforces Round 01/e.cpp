#pragma GCC diagnostic ignored "-Wunused-result"

#include <bits/stdc++.h>

const int INF = (int)1e9+1;

int table[1+30][1+30][1+50];

int solve(int n, int m, int k) {
    if (table[n][m][k] == -1) {
        if (k > n * m) {
            return table[n][m][k] = INF;
        } else if (k == n * m || k == 0) {
            return table[n][m][k] = 0;
        } else if (n == 1 || m == 1) {
            return table[n][m][k] = 1;
        } else {
            table[n][m][k] = INF;
            for (int m1 = 1; m1 < m; ++m1) {
                int m2 = m - m1;
                for (int k1 = 0; k1 <= k; ++k1) {
                    int k2 = k - k1;
                    table[n][m][k] = std::min(table[n][m][k], std::min(INF, std::min(INF, solve(n, m1, k1) + solve(n, m2, k2)) + n * n));
                }
            }
            for (int n1 = 1; n1 < n; ++n1) {
                int n2 = n - n1;
                for (int k1 = 0; k1 <= k; ++k1) {
                    int k2 = k - k1;
                    table[n][m][k] = std::min(table[n][m][k], std::min(INF, std::min(INF, solve(n1, m, k1) + solve(n2, m, k2) + m * m)));
                }
            }
        }
    }
    return table[n][m][k];
}

int main() {
    for (int i = 0; i <= 30; ++i) for (int j = 0; j <= 30; ++j) for (int k = 0; k <= 50; ++k) table[i][j][k] = -1;
    int nQ; scanf("%d", &nQ);
    for (int i = 0; i < nQ; ++i) {
        int n, m, k; scanf("%d %d %d", &n, &m, &k);
        printf("%d\n", solve(n, m, k));
    }
    return 0;
}