#include <stdio.h>
typedef long long ll;
int main() {
    int n, m, q; 
    scanf("%d %d %d", &n, &m, &q);
    static ll sum[1+1000][1+1000];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int value;
            scanf("%d", &value);
            sum[i][j] = value + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }
    while (q--) {
        int i1, j1, i2, j2;
        scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
        printf("%I64d\n", sum[i2][j2]-sum[i1-1][j2]-sum[i2][j1-1]+sum[i1-1][j1-1]);
    }
    return 0;
}