/*
    Problem: 43C. Lucky Tickets
    
    Solution: number theory, math, constructive, O(n * log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>

int main() {
    int n;
    while (std::cin >> n) {
        std::string s; int n0 = 0, n1 = 0, n2 = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> s;
            int rem = 0;
            for (char c : s) {
                rem += (c - '0');
            }
            rem %= 3;
            n0 += rem == 0;
            n1 += rem == 1;
            n2 += rem == 2;
        }
        std::cout << std::min(n1,n2) + n0 / 2 << std::endl;
    }
    return 0;
}