/*
    Problem: 467B. Fedor and New Game
    
    Solution: xor, bits, implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> arr;
    while (m--) {
        int v; std::cin >> v;
        arr.push_back(v);
    }
    int num, answ = 0; std::cin >> num;
    for (auto& it : arr) {
        answ += (__builtin_popcount(it ^ num) <= k);
    }
    std::cout << answ;
    return 0;
}