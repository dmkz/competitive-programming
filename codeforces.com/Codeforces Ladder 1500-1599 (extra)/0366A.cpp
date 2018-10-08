/*
    Problem: 366A. Dima and Guards
    
    Solution: implementation, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
const int INF = (int)1e9+1;
int main() {
    int sum; std::cin >> sum;
    int best_i = 0, best_a = INF, best_b = INF;
    for (int i = 0; i < 4; ++i) {
        int a1, b1, a2, b2; 
        std::cin >> a1 >> b1 >> a2 >> b2;
        int a = std::min(a1,b1);
        int b = std::min(a2,b2);
        if (a+b < best_a + best_b) {
            best_a = a;
            best_b = b;
            best_i = i+1;
        }
    }
    if (best_a + best_b <= sum) {
        std::cout << best_i << ' ' << best_a << ' ' << sum - best_a;
    } else {
        std::cout << -1;
    }
    return 0;
}