/*
    Problem: 271C. Secret
    
    Solution: math, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        std::vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            numbers[i] = i+1;
        }
        int begin = 2 * k;
        int after = begin + k;
        if (after > n) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::rotate(numbers.begin()+begin, numbers.begin()+begin+1, numbers.begin()+after);
        std::vector<int> answer(1+n);
        for (int i = 0; i < n; ++i) {
            answer[numbers[i]] = i % k + 1;
        }
        for (int i = 1; i <= n; ++i) {
            std::cout << answer[i] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}