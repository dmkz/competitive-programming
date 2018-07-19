/*
    Problem: 660A. Co-prime Array
    
    Solution: greedy, implementation, O(n*log(MAX_A))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) {
        std::cin >> it;
    }
    
    std::vector<int> b{a[0]};
    for (int i = 1; i < n; ++i) {
        if (gcd(a[i-1], a[i]) != 1) {
            b.push_back(1);
        }
        b.push_back(a[i]);
    }
    std::cout << b.size() - a.size() << std::endl;
    for (auto& it : b) {
        std::cout << it << ' ';
    }
    return 0;
}