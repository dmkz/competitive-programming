/*
    Problem: 567C. Geometric Progression
    
    Solution: hash table, custom hash, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct CustomHash {
    uint64_t operator()(uint64_t x) const {
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return x;
    }
};
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, k; std::cin >> n >> k; ) {
        gp_hash_table<int64_t, int, CustomHash> left, right;
        std::vector<int> arr(n);
        for (auto &it : arr) { std::cin >> it; right[it]++; }
        int64_t answ = 0;
        for (int i = 0; i < n; i++) {
            right[arr[i]]--;
            int cntL = 0, cntR = 0;
            if (k == 1) {
                cntR = right[arr[i]];
                cntL = left[arr[i]];
            } else if (arr[i] % k == 0) {
                cntR = right[arr[i] * 1LL * k];
                cntL = left[arr[i] / k];
            }
            answ += cntL * 1LL * cntR;
            left[arr[i]]++;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}