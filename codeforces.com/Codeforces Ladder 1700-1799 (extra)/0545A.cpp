/*
    Problem: 545A. Toy Cars
    
    Solution: implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> answ;
        for (int i = 1; i <= n; ++i) {
            bool bad = false;
            for (int j = 1; j <= n; ++j) {
                int v; std::cin >> v;
                bad = bad || v == 1 || v == 3;
            }
            if (!bad) {
                answ.push_back(i);
            }
        }
        std::cout << answ.size() << std::endl;
        for (auto it : answ) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}