/*
    Problem: 573B. Bear and Blocks
    
    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = (int)1e9+1;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(1+n+1), minLeft(1+n+1, INF), minRight(1+n+1, INF);
        minLeft[0] = 0; minRight[n+1] = 0;
        for (int i = 1; i <= n; ++i) {
            std::cin >> arr[i];
        }
        for (int i = 1; i <= n; ++i) {
            minLeft[i] = std::min(minLeft[i-1]+1, arr[i]);
        }
        for (int i = n; i >= 1; --i) {
            minRight[i] = std::min(minRight[i+1]+1, arr[i]);
        }
        int answ = 0;
        for (int i = 1; i <= n; ++i) {
            answ = std::max(std::min(minLeft[i], minRight[i]), answ);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}