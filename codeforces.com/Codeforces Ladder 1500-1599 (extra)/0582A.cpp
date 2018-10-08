/*
    Problem: 582A. GCD Table
    
    Solution: math, constructive, greedy, set, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <map>

#define size(x) (int)(x).size()

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n; std::cin >> n; std::map<int,int> cnt;
    for (int i = 0; i < n*n; ++i) {
        int v; std::cin >> v;
        cnt[-v]++;
    }
    std::vector<int> answ;
    for (auto& it : cnt) {
        auto x = -it.first;
        while (it.second > 0) {
            for (auto y : answ) {
                cnt[-gcd(x,y)] -= 2;
            }
            answ.push_back(x);
            it.second--;
        }
    }
    assert(size(answ) == n);
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}