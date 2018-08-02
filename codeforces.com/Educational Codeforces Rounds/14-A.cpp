/*
    Problem: 691A. Fashion in Berland
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    int nZeros = 0;
    for (int i = 0 ; i < n; ++i) {
        int v; std::cin >> v;
        nZeros += v == 0;
    }
    std::cout << (n == 1 ? (nZeros == 1 ? "NO" : "YES") : (nZeros == 1 ? "YES" : "NO"));
    return 0;
}