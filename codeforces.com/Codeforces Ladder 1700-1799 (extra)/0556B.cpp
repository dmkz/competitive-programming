/*
    Problem: 556B. Case of Fake Numbers
    
    Solution: math, constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

bool check(const std::vector<int>& a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != i) return false;
    }
    return true;
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> a(n);
        for (auto& it : a) { std::cin >> it; }
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            if (check(a)) {
                flag = true;
                break;
            }
            for (int j = 0; j < n; ++j) {
                a[j] = (n + a[j] + ((j % 2 == 0) ? +1 : -1)) % n;
            }
        }
        std::cout << (flag ? "Yes\n" : "No\n");
    }
    return 0;
}