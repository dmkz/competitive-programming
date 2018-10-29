/*
    Problem: 361B. Levko and Permutation
    
    Solution: constructive, permutation, gcd, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cassert>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

std::vector<int> solve(int n, int k) {
    if (n == 1) {
        return k == 0 ? std::vector<int>{1} : std::vector<int>{-1};
    }
    std::vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = i+1;
    }
    int cnt = n-1; bool was = false;
    if (cnt % 2 != k % 2) {
        std::swap(perm[0], perm[1]);
        cnt--;
        was = true;
    }
    for (int i = 1 + was; cnt > k && i < n; i += 2) {
        std::swap(perm[i], perm[i+1]);
        cnt -= 2;
    }
    if (cnt != k) {
        perm.assign(1, -1);
    } else {
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            res += gcd(i, perm[i-1]) > 1;
        }
        assert(res == k);
    }
    return perm; 
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, k;
    while (std::cin >> n >> k) {
        auto perm = solve(n, k);
        for (auto& it : perm) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}