/*
    Problem: 846C. Four Segments
    
    Solution: brute force, prefix sums, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

typedef long long ll;

int main() {
    // Input:
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    // Calculate prefix sums:
    std::vector<ll> sum{0};
    for (auto& it : arr) sum.push_back(sum.back() + it);
    // Function for query to sum on segment [l, r):
    std::function<ll(int,int)> get_sum = [&](int l, int r) {
        return sum[r] - sum[l];
    };
    // Temporary best answer:
    ll best = std::accumulate(arr.begin(), arr.end(), ll(0));
    int delim1 = n, delim2 = n, delim3 = n;
    // Brute mid and find best sum(0, pos1) - sum(pos1, mid) + sum(mid, pos2) - sum(pos2, n):
    for (int mid = 0; mid <= n; ++mid) {
        ll max1 = get_sum(0, mid); int pos1 = mid;
        for (int i = 0; i <= mid; ++i) {
            auto s1 = get_sum(0, i);
            auto s2 = get_sum(i, mid);
            if (s1 - s2 > max1) {
                max1 = s1 - s2;
                pos1 = i;
            }
        }
        ll max2 = get_sum(mid, n); int pos2 = n;
        for (int j = mid; j <= n; ++j) {
            auto s1 = get_sum(mid, j);
            auto s2 = get_sum(j, n);
            if (s1 - s2 > max2) {
                max2 = s1 - s2;
                pos2 = j;
            }
        }
        if (max1 + max2 > best) {
            best = max1+max2;
            delim1 = pos1;
            delim2 = mid;
            delim3 = pos2;
        }
    }
    printf("%d %d %d", delim1, delim2, delim3);
    return 0;
}