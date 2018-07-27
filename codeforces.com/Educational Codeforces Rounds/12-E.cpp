/*
    Problem: 665E. Beautiful Subarrays
    
    Solution: sort, binary search, implicit prefix tree, O(n*log(n)*W)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, limit; std::cin >> n >> limit;
    
    // Calculate xor-sums on prefixes:
    std::vector<int> sum{0};
    for (int i = 0; i < n; ++i) {
        int value; std::cin >> value;
        sum.push_back(sum.back() ^ value);
    }

    std::sort(sum.begin(), sum.end());
    
    // After sorting we have implicit prefix tree
    // For each position i we need to add number of sum[i] ^ sum[j] >= limit, j from i+1 to n
    ll answ = 0;
    for (int i = 0; i <= n; ++i) {
        int left = i+1, right = n;
        for (int pow = 30; right >= left && pow >= 0; --pow) {
            // binary search on first 1 bit and last 0 bit:
            int low = left-1, high = right+1;
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (((sum[mid] >> pow) & 1) == 0) {
                    low = mid;
                } else {
                    high = mid;
                }
            }
            assert(high >= left && low <= right);
            
            if (((limit >> pow) & 1) == 0) {
                // We need to add number of elements which gives 1 after XOR with i-th item
                if (((sum[i] >> pow) & 1) == 1) {
                    answ += high - left;
                    left = high; // move to [high, right] segment (contains bit 1 on pow place)
                } else {
                    answ += right - low;
                    right = low; // move to [left, low] segment (contains bit 0 on pow place)
                    
                }
            } else {
                if (((sum[i] >> pow) & 1) == 1) {
                    right = low; // move to [left, low] segment (contains bit 0 on pow place)
                } else {
                    left = high; // move to [high, right] segment (contains bit 1 on pow place)
                }
            }
        }
        // Add equal to limit range of array:
        answ += right - left + 1;
    }
    std::cout << answ;
    return 0;
}