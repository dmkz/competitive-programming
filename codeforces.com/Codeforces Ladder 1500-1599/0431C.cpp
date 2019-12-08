/*
    Problem: 431C. k-Tree
    Solution: dynamic programming, trees, implementation
*/
#include <iostream>
#include <algorithm>
#include <vector>

const int mod = (int)1e9+7;

void add(int& a, int b) {
    if ((a += b) >= mod) a -= mod;
}

int main() {
    int n, k, d;
    std::cin >> n >> k >> d;
    
    std::vector<std::vector<int>> count(2, std::vector<int>(1+n)); // count[was edge >= d][sum edges]
    count[0][0] = 1;
    for (int sum = 0; sum < n; ++sum) {
        for (int edge = 1; edge <= k; ++edge) {
            if (sum+edge <= n) {
                add(count[edge >= d][sum+edge], count[0][sum]);
                add(count[1][sum+edge], count[1][sum]);
            }
        }
    }
    std::cout << count[1][n];
    return 0;
}