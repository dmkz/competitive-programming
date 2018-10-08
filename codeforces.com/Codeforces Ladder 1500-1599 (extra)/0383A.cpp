/*
    Problem: 383A. Milking cows
    
    Solution: greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    
    int nZeros = 0, nOnes = 0;
    for (auto& it : a) {
        nZeros += (it == 0);
        nOnes  += (it == 1);
    }
    if (nOnes > nZeros) {
        std::swap(nOnes, nZeros);
        std::reverse(a.begin(), a.end());
        for (auto& it : a) it = 1 - it;
    }
    // nOnes <= nZeros;
    int64_t answ = 0;
    for (int i = n-1; i >= 0; --i) {
        if (a[i] == 1) {
            nOnes--;
        } else {
            answ += nOnes;
        }
    }
    std::cout << answ;
    return 0;
}