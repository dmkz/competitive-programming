/*
    Problem: 369A. Valera and Plates
    
    Solution: greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n, n1, n2, u1 = 0, u2 = 0, answ = 0; 
    std::cin >> n >> n1 >> n2;
    for (int i = 0; i < n; ++i) {
        int a; std::cin >> a;
        if (a == 1) {
            if (u1 == n1) {
                u1--; answ++;
            }
            u1++;
        } else {
            if (u1 == n1 && u2 == n2) {
                u1--; answ++; u1++;
            } else if (u1 == n1) {
                u2++;
            } else if (u2 == n2) {
                u1++;
            } else {
                u2++;
            }
        }
    }
    std::cout << answ;
    return 0;
}