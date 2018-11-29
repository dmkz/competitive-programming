/*
    Problem: 560A. Currency System in Geraldion
    
    Solution: constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        bool is1 = false;
        for (int i = 0, v; i < n; ++i) {
            std::cin >> v;
            is1 = is1 || v == 1;
        }
        std::cout << (is1 ? -1 : 1) << std::endl;
    }
    return 0;
}