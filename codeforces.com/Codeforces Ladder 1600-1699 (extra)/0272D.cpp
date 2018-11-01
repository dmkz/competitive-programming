/*
    Problem: 272D. Dima and Two Sequences
    
    Solution: math, combinatorics, binary pow, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define all(x) (x).begin(), (x).end()
#define binpos(x, y) int(std::lower_bound(all(x), y) - (x).begin())
#define unique(x) (x).erase(std::unique(all(x)), (x).end())

typedef long long Int;

Int pow(Int a, Int n, Int mod) {
    Int res = 1 % mod;
    while (n > 0) {
        if (n & 1) {
            res = res * a % mod;
        }
        n >>= 1;
        a = a * a % mod;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        // Input:
        std::vector<int> a(n), b(n), x;
        for (auto& it : a) { std::cin >> it; x.push_back(it); }
        for (auto& it : b) { std::cin >> it; x.push_back(it); }
        Int mod; std::cin >> mod;
        // Calculate counts:
        std::sort(all(x));
        unique(x);
        int sz = (int)x.size();
        std::vector<int> cnt(sz, 0), dec(sz, 0);
        for (int i = 0, pa, pb; i < n; ++i) {
            cnt[pa = binpos(x, a[i])]++;
            cnt[pb = binpos(x, b[i])]++;
            dec[pa] += (pa == pb);
        }
        // Calculate factorials:
        std::vector<Int> factWithout2(1+2 * n, 1), count2(1+2*n, 0);
        for (Int i = 2; i <= 2 * n; ++i) {
            count2[i] = count2[i-1];
            Int j = i;
            while (j % 2 == 0) { count2[i]++, j /= 2; }
            factWithout2[i] = factWithout2[i-1] * j % mod;
        }        
        // Calculate answer:
        Int answ = 1;
        for (Int i = 0; i < sz; ++i) {
            answ = answ * factWithout2[cnt[i]] % mod * pow(2, count2[cnt[i]] - dec[i], mod) % mod;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}