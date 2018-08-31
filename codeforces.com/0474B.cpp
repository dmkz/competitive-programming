/*
    Problem: 474B. Worms
    
    Solution: binary search, prefix sums, O(n + q * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> s{0};
    for (int i = 0, v; i < n; ++i) { 
        scanf("%d", &v); 
        s.push_back(s.back() + v); 
    }
    int q; scanf("%d", &q);
    while (q--) {
        int v; scanf("%d", &v);
        int low = 0, high = n+1;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (s[mid] >= v) {
                high = mid;
            } else low = mid;
        }
        printf("%d\n", high);
    }
    return 0;
}