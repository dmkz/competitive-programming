/*
    Problem: 358D. Dima and Hares
    
    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int INF = (int)1e9;

int solve(int n, const vvi& arr) {
    // 0 - no waiting for everyone
    // 1 - wait for hare on the left side
    // 2 - wait for hare on the right side
    // 3 - wait for hares on the both sides
    vvi max(4, vi(n, -INF));
    max[0][0] = arr[0][0];
    max[2][0] = arr[1][0];
    for (int p = 1; p < n; ++p) {
        // place without neighbours:
        max[0][p] = std::max(max[2][p-1], max[3][p-1]) + arr[0][p];
        // place with waiting of left neighbour:
        max[1][p] = std::max(max[1][p-1], max[0][p-1]) + arr[1][p];
        // place with waiting of right neighbour:
        max[2][p] = std::max(max[2][p-1], max[3][p-1]) + arr[1][p];
        // place with waiting of both neighbours:
        max[3][p] = std::max(max[1][p-1], max[0][p-1]) + arr[2][p];
    }
    return std::max(max[0][n-1], max[1][n-1]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vvi arr(3, vi(n));
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> arr[i][j];
            }
        }
        std::cout << solve(n, arr) << std::endl;
    }
    return 0;
}