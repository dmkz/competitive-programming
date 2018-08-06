/*
    Problem: 1016A. Death Note
    
    Solution: greedy, implementation, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m; std::cin >> n >> m;
    ll cur = 0;
    for (int i = 0; i < n; ++i) {
        int a; std::cin >> a;
        std::cout << (cur + a) / m << ' ';
        cur = (cur + a) % m;
    }
    
    return 0;
}