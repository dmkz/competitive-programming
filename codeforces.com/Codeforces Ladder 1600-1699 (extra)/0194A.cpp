/*
    Problem: 194A. Exams
    
    Solution: brute force, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

int solve(int n, int sum) {
    int min = n;
    for (int n5 = 0; n5 <= n; ++n5) {
        for (int n4 = 0; n4 + n5 <= n; ++n4) {
            for (int n3 = 0; n3 + n4 + n5 <= n; ++n3) {
                int n2 = n - n3 - n4 - n5;
                if (n5 * 5 + n4 * 4 + n3 * 3 + n2 * 2 == sum) {
                    min = std::min(min, n2);
                }
            }
        }
    }
    return min;
}

int main() {
    int n, sum;
    while (std::cin >> n >> sum) {
        std::cout << solve(n, sum) << std::endl;
    }
    return 0;
}