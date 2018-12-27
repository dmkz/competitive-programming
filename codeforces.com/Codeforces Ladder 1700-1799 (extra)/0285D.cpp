/*
    Problem: 285D. Permutation Sum
    
    Solution: brute force, precalc, O(n!)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef std::vector<int> vi;

int fact(int n) {
    return n == 1 ? 1 : fact(n-1) * n;
}

int64_t fast(int n) {
    vi a(n), b(n), cnt(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    int64_t answ = 0;
    for (int i = 0; i < n; ++i) {
        b[i] = i;
    }
    do {
        cnt.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            cnt[(a[i]+b[i])%n]++;
        }
        bool good = true;
        for (int i = 0; i < n; ++i) {
            good = good && cnt[i];
        }
        answ += good;
    } while (std::next_permutation(all(b)));
    return answ;
}

int main() {
    std::vector<int64_t> precalc = {1,3,15,133,2025,37851,1030367,36362925};
    /*for (int i = 1; i <= 13; i += 2) {
        std::cout << "fast answ for n = " << i << " equal to " << fast(i) << std::endl;
    } */
    const int mod  = (int)1e9+7;
    int n;
    while (std::cin >> n) {
        if (n % 2 == 0) {
            std::cout << 0 << std::endl;
        } else {
            int64_t temp = precalc[(n-1)/2] % mod;
            for (int i = 1; i <= n; ++i) {
                temp = temp * i % mod;
            }
            std::cout << temp << std::endl;
        }
    }
    return 0;
}