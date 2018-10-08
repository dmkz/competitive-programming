/*
    Problem: 244B. Undoubtedly Lucky Numbers
    
    Solution: brute force, O(max^2 * len^2 * 2^len)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> numbers{1000*1000*1000};
    for (int len = 1; len < 10; ++len) {
        for (int d1 = 0; d1 <= 9; ++d1) {
            for (int d2 = 0; d2 <= 9; ++d2) {
                for (int mask = 0; mask < (1 << len); ++mask) {
                    int number = 0;
                    for (int i = 0; i < len; ++i) {
                        number *= 10;
                        number += ((mask >> i) & 1) ? d1 : d2;
                    }
                    if (number > 0) {
                        numbers.push_back(number);
                    }
                }
            }
        }
    }
    std::sort(numbers.begin(), numbers.end());
    numbers.erase(std::unique(numbers.begin(), numbers.end()), numbers.end());
    int answ = 0;
    while (answ < (int)numbers.size() && numbers[answ] <= n) ++answ;
    printf("%d", answ);
    return 0;
}