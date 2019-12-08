/*
    Problem: 285C. Building Permutation
    Solution: sorting, greedy, implementation
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end());
    int64_t res = 0;
    for (int i = 0; i < n; ++i) res += std::abs(a[i] - i - 1);
    std::cout << res;
    return 0;
}