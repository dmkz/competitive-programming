/*
    Problem: 340D. Bubble Sort Graph
    
    Solution: dynamic programming, binary search, longest increasing subsequence, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#define all(x) (x).begin(), (x).end()
const int INF = (int)1e9;
int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n), maxLen(n), item(1+n, INF);
    item[0] = -INF;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; ++i) {
        maxLen[i] = int(std::lower_bound(all(item), arr[i])-item.begin());
        item[maxLen[i]] = std::min(item[maxLen[i]], arr[i]);
    }
    printf("%d\n", *std::max_element(all(maxLen)));
    return 0;
}