/*
    Problem: 651A. Joysticks
    
    Solution: greedy, implementation, O(a+b)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int a,b;
    while (std::cin >> a >> b) {
        int answ = 0;
        while (a > 0 && b > 0) {
            if (a == 1 && b == 1) {
                break;
            }
            if (a < b) {
                a++,b-=2;
            } else {
                b++,a-=2;
            }
            ++answ;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}