/*
    Problem: 257D. Sum
    
    Solution: brute force, greedy, math, O(n * 8)
    
    Author: Dmitry Kozyrev, github, dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>

typedef long long ll;

const ll INF = (ll)1e18L+7;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        // Prepare arrays:
        std::vector<ll> arr(n);
        std::string signs(n, '+');
        std::vector<ll> inverseFrom(n+1);
        // Input:
        for (auto &it : arr) { std::cin >> it; }
        // We will try combine last three items to one item that will provide required condition:
        int nBrute; 
        while (n > 1) {
            nBrute = std::min(3, n);
            ll best_res = INF, best_mask = -1, limit = ((nBrute == n) ? (arr[0]) : (2 * arr[n - nBrute - 1]));
            for (ll mask = 0; mask < (1 << nBrute); ++mask) {
                ll res = 0;
                for (ll bit = 0; bit < nBrute; ++bit) {
                    res += (((mask >> bit) & 1) ? arr[n - nBrute + bit] : -arr[n - nBrute + bit]);
                }
                if (0 <= res && res <= limit && res < best_res) {
                    best_res = res, best_mask = mask;
                }
            }
            assert(best_mask != -1);
            for (ll bit = 0; bit < nBrute; ++bit) {
                if ((best_mask >> bit) & 1) {
                    // nothing
                } else {
                    inverseFrom[n - nBrute + bit]++;
                    if (bit+1 < nBrute) {
                        inverseFrom[n - nBrute + bit + 1]--;
                    }
                }
            }
            for (int i = 0; i < nBrute; ++i) { arr.pop_back(); }
            arr.push_back(best_res);
            n = n - nBrute + 1;
        }
        for (int i = 0, balance = 0; i < (int)signs.size(); ++i) {
            (balance += int(inverseFrom[i] % 2)) %= 2;
            if (balance) { signs[i] = '-'; }
        }
        std::cout << signs << std::endl;
    }
    return 0;
}