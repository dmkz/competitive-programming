/*
    Problem: 222C. Reducing Fractions
    
    Solution: number theory, sieve, primes, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef std::vector<int> vi;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    const int NMAX = (int)1e7;
    vi firstPrimeDivisor(1+NMAX);
    for (int i = 2; i * i <= NMAX; ++i) {
        if (firstPrimeDivisor[i]) {
            continue;
        }
        firstPrimeDivisor[i] = i;
        for (int j = i * i; j <= NMAX; j += i) {
            if (!firstPrimeDivisor[j]) {
                firstPrimeDivisor[j] = i;
            }
        }
    }
    for (int i = 2; i <= NMAX; ++i) {
        if (!firstPrimeDivisor[i]) {
            firstPrimeDivisor[i] = i;
        }
    }
    std::function<vi(int)> getPrimes = [&](int number) {
        vi answ;
        while (number > 1) {
            answ.push_back(firstPrimeDivisor[number]);
            number /= firstPrimeDivisor[number];
        }
        return answ;
    };
    int n, m;
    while (std::cin >> n >> m) {
        vi cntA(1+NMAX,0), cntB(1+NMAX,0), gcd(1+NMAX,0);
        vi a(n), b(m);
        for (auto &it : a) {
            std::cin >> it;
            for (int p : getPrimes(it)) {
                cntA[p]++;
            }
        }
        for (auto &it : b) {
            std::cin >> it;
            for (int p : getPrimes(it)) {
                cntB[p]++;
            }
        }
        for (int it = 0; it <= NMAX; ++it) {
            gcd[it] = std::min(cntA[it], cntB[it]);
        }
        cntA = gcd, cntB = gcd;
        for (auto &it : a) {
            for (int p : getPrimes(it)) {
                if (cntA[p] > 0) {
                    assert(it % p == 0);
                    it /= p;
                    cntA[p]--;
                }
            }
        }
        for (auto &it : b) {
            for (int p : getPrimes(it)) {
                if (cntB[p] > 0) {
                    assert(it % p == 0);
                    it /= p;
                    cntB[p]--;
                }
            }
        }
        std::cout << n << ' ' << m << '\n';
        for (auto it : a) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
        for (auto it : b) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
        std::cout << std::endl;
    }
    return 0;
}