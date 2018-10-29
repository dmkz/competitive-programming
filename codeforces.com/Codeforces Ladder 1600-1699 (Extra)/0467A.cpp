/*
    Problem: 467A. George and Accommodation
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        int answ = 0;
        while (n--) {
            int p, q; std::cin >> p >> q;
            answ += q - p >= 2;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}