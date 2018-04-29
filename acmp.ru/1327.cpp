#include <stdio.h>
#include <vector>
#include <algorithm>

int main() {
    int n, k; 
    scanf("%d %d", &n, &k);
    
    std::vector<int> a(n);
    for (auto& it : a) {
        scanf("%d", &it);
    }
    
    int64_t sum = std::accumulate(a.begin(), a.end(), 0LL);
    if (sum < k) {
        printf("0\n");
        return 0;
    }
    
    int64_t low = 1, high = sum;
    while (high - low > 1) {
        int64_t mid = (low + high) / 2;
        int c = 0;
        for (auto it : a) {
            c += it / mid;
        }
        if (c >= k) {
            low = mid;
        } else {
            high = mid;
        }
    }
    printf("%d\n", low);
    
    return 0;
}