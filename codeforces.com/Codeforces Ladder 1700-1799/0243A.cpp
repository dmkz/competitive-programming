/*
    Problem: 243A. The Brand New Function
    
    Solution: binary search, sparse table, O(n*log(n)^2 + AMAX)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // Preparing
    const int NMAX = (int)1e5, AMAX = 1024*1024, PMAX = 17;
    static int arr[NMAX], log2[1+NMAX], bitwise_or[PMAX][NMAX];
    for (int i = 2; i <= NMAX; ++i) { log2[i] = 1 + log2[i/2]; }
    // Solution:
    for (int n; std::cin >> n; ) {
        std::vector<bool> can(AMAX);
        // Input:
        for (int i = 0; i < n; ++i) { std::cin >> arr[i]; }
        // Build sparse table:
        for (int i = 0; i < n; ++i) { bitwise_or[0][i] = arr[i]; }
        for (int p = 1; p < PMAX; ++p) {
            for (int i = 0; i + (1 << p) - 1 < n; ++i) {
                bitwise_or[p][i] = bitwise_or[p-1][i] | bitwise_or[p-1][i + (1 << (p-1))];
            }
        }
        for (int i = 0; i < n; ++i) {
            int x = arr[i];
            int j = i;
            while (j < n) {
                can[x] = true;
                int low = j, high = n;
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    int p = log2[mid-i+1];
                    int y = bitwise_or[p][i] | bitwise_or[p][mid + 1 - (1 << p)];
                    if (y == x) { low = mid; }
                    else { high = mid; }
                }
                if (high == n) { break; }
                int p = log2[high-i+1];
                int y = bitwise_or[p][i] | bitwise_or[p][high + 1 - (1 << p)];
                x = y;
                j = high;
            }
        }
        int answ = 0;
        for (int x = 0; x < AMAX; ++x) {
            answ += (can[x]);
        }
        std::cout << answ << '\n';
    }
    return 0;
}