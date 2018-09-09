/*
    Problem: 792B. Counting-out Rhyme
    
    Solution: math, implementation, O(n+k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, k; std::cin >> n >> k;
    std::vector<int> a(k);
    for (auto& it : a) std::cin >> it;
    int cur = 0;
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) b[i] = i+1;
    for (auto& rem : a) {
        cur = (cur + rem) % n;
        std::cout << b[cur] << ' ';
        b.erase(b.begin() + cur);
        --n;
    }
    return 0;
}