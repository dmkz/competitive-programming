/*
    Problem: 286A. Lucky Permutation
    
    Solution: brute force, researching, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

bool check(int n, const std::vector<int>& p) {
    for (int i = 1; i <= n; ++i) {
        if (p[p[i]] != n - i + 1) return false;
    }
    return true;
}

std::vector<int> fast(int n) {
    if (n == 1) return {0, 1};
    std::vector<int> p(1+n);
    if (n % 2 == 1) {
        p[(n+1) / 2] = (n+1)/2;
    }
    int item = 2;
    for (int i = 1; i <= n; ++i) {
        if (p[i] == 0) {
            p[i] = item;
            item += 2;
            for (int cnt = 0, j = i; cnt < 4; ++cnt) {
                p[p[j]] = n-j+1;
                j = p[j];
            }
        }
    }
    return check(n, p) ? p : std::vector<int>();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        auto p = fast(n);
        if (p.empty()) {
            std::cout << " -1";
        } else {
            for (int i = 1; i <= n; ++i) {
                std::cout << " " << p[i];
            }
        }
        std::cout << std::endl;
    }
    return 0;
}