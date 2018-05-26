#include <stdio.h>
#include <vector>
typedef long long ll;
int main() {
    int n; 
    scanf("%d", &n);
    std::vector<ll> sum(1+n);
    for (int i = 1; i <= n; ++i) {
        int value;
        scanf("%d", &value);
        sum[i] = sum[i-1] + value;
    }
    int nQueries; 
    scanf("%d", &nQueries);
    while (nQueries--) {
        int l, r; 
        scanf("%d %d", &l, &r);
        printf("%I64d\n", sum[r] - sum[l-1]);
    }
    return 0;
}