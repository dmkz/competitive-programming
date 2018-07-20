/*
    Problem: 620B. Grandfather Dovlet’s calculator
    
    Solution: implementation, O(n*log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::vector<int> digit_count = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int a, b; std::cin >> a >> b;
    int sum = 0;
    for (int i = a; i <= b; ++i) {
        for (int temp = i; temp > 0; temp /= 10) {
            sum += digit_count[temp % 10];
        }
    }
    std::cout << sum << std::endl;
    
    return 0;
}