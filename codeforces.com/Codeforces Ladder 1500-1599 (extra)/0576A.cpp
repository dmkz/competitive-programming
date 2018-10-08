/*
    Problem: 576A. Vasya and Petya's Game
    
    Solution: number theory, sieve, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n; std::cin >> n;
    std::vector<bool> prime(1+n, true);
    prime[0] = prime[1] = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (!prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            prime[j] = 0;
        }
    }
    std::vector<int> answ;
    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) continue;
        int p = i;
        do {
            answ.push_back(p);
            p *= i;
        } while (p <= n);
    }
    std::cout << answ.size() << '\n';
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}