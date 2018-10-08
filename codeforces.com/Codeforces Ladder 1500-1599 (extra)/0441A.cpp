/*
    Problem: 441A. Valera and Antique Items
    
    Solution: implementation, O(n*k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
const int INF = (int)1e9+1;
int main() {
    int n, s; std::cin >> n >> s;
    std::vector<int> answ;
    for (int i = 1; i <= n; ++i) {
        int k; std::cin >> k; int min = INF;
        while (k--) { int val; std::cin >> val; if (min > val) min = val; }
        if (min < s) { answ.push_back(i); }
    }
    std::cout << answ.size() << '\n';
    for (auto& it : answ) std::cout << it << ' ';
    return 0;
}