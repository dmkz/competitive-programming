/*
    Problem: 432B. Football Kit
    
    Solution: implementation, combinatorics, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

const int MAX = (int)1e5;

int main() {
    int n; std::cin >> n;
    std::vector<int> hcnt(1+MAX), acnt(1+MAX), htype(n), atype(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> htype[i] >> atype[i];
        hcnt[htype[i]]++;
        acnt[atype[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        int h = hcnt[atype[i]] + (n-1);
        int a = n-1 - hcnt[atype[i]];
        std::cout << h << ' ' << a << '\n';
    }
    return 0;
}