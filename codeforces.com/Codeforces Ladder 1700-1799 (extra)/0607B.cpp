/*
    Problem: 607B. Zuma
    
    Solution: dynamic programming, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int solve(const std::vector<int>& arr) {
    std::vector<std::vector<int>> minTime(arr.size(), std::vector<int>(arr.size(), 0));
    // minTime[l][r] = minimal time for erasing seg [l,r]
    for (int i = 0; i < (int)arr.size(); ++i) { 
        minTime[i][i] = 1;
        if (i+1 < (int)arr.size()) {
            minTime[i][i+1] = 1 + (arr[i] != arr[i+1]);
        }
    }
    for (int len = 3; len <= (int)arr.size(); ++len) {
        for (int lt = 0; lt + len - 1 < (int)arr.size(); ++lt) {
            const int rt = lt + len - 1;
            minTime[lt][rt] = std::min(
                1 + minTime[lt+1][rt],
                minTime[lt][lt+1] + minTime[lt+2][rt]
            );
            // (arr[lt] == arr[mid] --> then we can include items on positions `lt` and `mid` in last removing for [lt+1, mid-1] seg
            for (int mid = lt + 2; mid <= rt; ++mid) {
                if (arr[lt] != arr[mid]) { continue; }
                minTime[lt][rt] = std::min(
                    minTime[lt][rt],
                    minTime[lt+1][mid-1] + (mid+1 > rt ? 0 : minTime[mid+1][rt])
                );
            }
        }
    }
    return minTime[0][(int)arr.size()-1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto &it : arr) { std::cin >> it; }
        std::cout << solve(arr) << std::endl;
    }
    return 0;
}