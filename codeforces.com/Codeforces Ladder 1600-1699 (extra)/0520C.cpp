/*
    Problem: 520C. DNA Alignment
    
    Solution: greedy, math, combinatorics, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

const int mod = (int)1e9+7;

int pow(int a, int n) {
    int ret = 1;
    while (n > 0) {
        if (n & 1) {
            ret = int(1LL * ret * a % mod);
        }
        a = int(1LL * a * a % mod);
        n >>= 1;
    }
    return ret;
}

int solve(const std::string& s) {
    int sA = 0, sT = 0, sG = 0, sC = 0;
    for (auto& it : s) {
        sA += (it == 'A');
        sT += (it == 'T');
        sG += (it == 'G');
        sC += (it == 'C');
    }
    int max = std::max({sA, sT, sG, sC});
    int nMax = (sA == max) + (sT == max) + (sG == max) + (sC == max);
    return pow(nMax, (int)s.size());
}

int main() {
    int n; std::string s;
    while (std::cin >> n >> s) {
        std::cout << solve(s) << std::endl;
    }
    return 0;
}