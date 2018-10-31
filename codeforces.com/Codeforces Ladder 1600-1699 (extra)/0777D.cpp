/*
    Problem: 777D. Cloud of Hashtags
    
    Solution: greedy, strings, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

int find_diff(const std::string& a, const std::string& b) {
    int p = 0;
    while (p < (int)a.size() && p < (int)b.size() && a[p] == b[p]) {++p;}
    return p;
}

void fix(std::string& a, std::string& b) {
    int p = find_diff(a, b);
    if (p == (int)a.size()) {
        return;
    }
    if (p == (int)b.size()) {
        assert(a.size() >= b.size());
        a.resize(b.size());
        return;
    }
    if (a[p] > b[p]) {
        a.resize(p);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<std::string> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        for (int i = n-2; i >= 0; --i) {
            fix(arr[i], arr[i+1]);
        }
        for (auto& it : arr) {
            std::cout << it << "\n";
        }
    }
    return 0;
}