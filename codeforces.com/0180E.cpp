/*
    Problem: 180E. Cubes
    
    Solution: binary search, two pointers, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>

int main() {
    int nItems, nColors, nDel;
    scanf("%d %d %d", &nItems, &nColors, &nDel);
    std::vector<int> items(nItems);
    for (auto& it : items) scanf("%d", &it);
    std::function<bool(int)> can = [&](const int len) {
        int l = 0, r = -1;
        std::vector<int> count(1+nColors);
        while (l < nItems) {
            while (r+1 < nItems && r+1-l+1 <= len + nDel) {
                r++;
                count[items[r]]++;
                if (count[items[r]] >= len) {
                    return true;
                }
            }
            count[items[l++]]--;
        }
        return false;
    };
    int low = 0, high = nItems+1;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (can(mid)) {
            low = mid;
        } else high = mid;
    }
    printf("%d", low);
    return 0;
}