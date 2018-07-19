/*
    Problem: 660B. Seating On Bus
    
    Solution: implementation, O(n)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> arr(4, std::vector<int>(1+n));
    int number = 1;
    for (int i = 1; number <= m && i <= n; ++i) {
        arr[0][i] = number++;
        if (number <= m) {
            arr[3][i] = number++;
        }
    }
    for (int i = 1; number <= m && i <= n; ++i) {
        arr[1][i] = number++;
        if (number <= m) {
            arr[2][i] = number++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (arr[1][i] != 0) {
            std::cout << arr[1][i] << ' ';
        }
        if (arr[0][i] != 0) {
            std::cout << arr[0][i] << ' ';
        }
        if (arr[2][i] != 0) {
            std::cout << arr[2][i] << ' ';
        }
        if (arr[3][i] != 0) {
            std::cout << arr[3][i] << ' ';
        }
    }
    return 0;
}