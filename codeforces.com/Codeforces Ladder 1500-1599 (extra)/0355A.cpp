/*
    Problem: 355A. Vasya and Digital Root
    
    Solution: constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>

int main() {
    int k, d; std::cin >> k >> d;
    if (d == 0 && k > 1) {
        std::cout << "No solution"; return 0;
    }
    std::string s; s.push_back(char('0' + d));
    while ((int)s.size() < k) s.push_back('0');
    std::cout << s;
    return 0;
}