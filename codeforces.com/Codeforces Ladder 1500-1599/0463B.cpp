/*
    Problem: 463B. Caisa and Pylons
    Solution: brute force, implementation, math
*/
#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
int main() {
    int n; std::cin >> n;
    std::vector<int> h(1+n);
    ll cur = 0, min = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> h[i];
        cur += h[i-1] - h[i];
        min = std::min(min, cur);
    }
    std::cout << -min;
    return 0;
}