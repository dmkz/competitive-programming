/*
    Problem: 1184. Cable Master
    
    Solution: binary search, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <cmath>
#include <functional>

int main() {
    int n, need; scanf("%d %d", &n, &need);
    std::vector<int> arr;
    for (int i = 0; i < n; ++i) {
        double val; scanf("%lf", &val); // 1.00 <= val <= 100 000.00
        arr.push_back((int)std::round(val * 100));
    }
    std::function<bool(int)> can = [&](const int val) {
        int s = 0;
        for (auto it : arr) {
            s += it / val;
            if (s >= need) return true;
        }
        return false;
    };
    int low = 0, high = 100*1000*100+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(mid)) {
            low = mid;
        } else high = mid;
    }
    printf("%0.2f", low * 0.01);
    return 0;
}