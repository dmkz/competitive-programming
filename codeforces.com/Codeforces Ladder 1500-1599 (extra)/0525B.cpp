/*
    Problem: 525B. Pasha and String
    
    Solution: strings, implementation, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

int main() {
    std::string s; int q;
    std::cin >> s >> q;
    const int n = (int)s.size();
    std::vector<int> add(n), dec(n);
    while (q--) {
        int a; std::cin >> a; --a;
        assert(0 <= a && a < n);
        assert(0 <= n-a-1 && n-a-1 < n);
        add[a]++; dec[n-a-1]++;
    }
    std::vector<int> balance(n);
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        bal += add[i];
        balance[i] = bal % 2;
        bal -= dec[i];
    }
    for (int i = 0, j = n-1; i <= j; ++i, --j) {
        if (balance[i]) {
            std::swap(s[i], s[j]);
        }
    }
    std::cout << s;
    return 0;
}