/*
    Problem: 689D. Friends and Subsequences
    
    Solution: binary search, sparse table, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    // Sparse tables' parameters:
    const int PMAX = 18, NMAX = 256 * 1024;
    static int max[PMAX][NMAX], min[PMAX][NMAX], log[NMAX];
    for (int i = 2; i < NMAX; ++i) {
        log[i] = log[i / 2] + 1;
    }
    int n;
    while (std::cin >> n) {
        // Input `a` sequence:
        for (int i = 0; i < n; ++i) {
            std::cin >> max[0][i];
        }
        // Input `b` sequence:
        for (int i = 0; i < n; ++i) {
            std::cin >> min[0][i];
        }
        // Build sparse tables for `max` over `a` and `min` over `b`:
        for (int p = 1; p < PMAX; ++p) {
            for (int i = 0; i + (1 << p) - 1 < n; ++i) {
                max[p][i] = std::max(max[p-1][i], max[p-1][i+(1<<(p-1))]);
                min[p][i] = std::min(min[p-1][i], min[p-1][i+(1<<(p-1))]);
            }
        }
        // Queries to min / max:
        std::function<int(int,int)> get_min = [&](int l, int r) {
            int len = r - l + 1; int pow = log[len];
            return std::min(min[pow][l], min[pow][r-(1 << pow)+1]);
        };
        std::function<int(int,int)> get_max = [&](int l, int r) {
            int len = r - l + 1; int pow = log[len];
            return std::max(max[pow][l], max[pow][r-(1 << pow)+1]);
        };
        // Calculate number of equal subsegments using binary search:
        int64_t answ = 0;
        for (int i = 0; i < n; ++i) {
            int begin, end;
            { // upper bound:
                int low = i-1, high = n;
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (get_min(i, mid) < get_max(i, mid)) {
                        high = mid;
                    } else {
                        low = mid;
                    }
                }
                end = high;
            }
            { // lower bound:
                int low = i-1, high = end;
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (get_min(i, mid) > get_max(i, mid)) {
                        low = mid;
                    } else {
                        high = mid;
                    }
                }
                begin = high;
            }
            // Equal range:
            answ += end - begin;
        }
        std::cout << answ << std::endl;
    }
    
    return 0;
}