/*
    Problem: 416B. Art Union
    
    Solution: implementation, O(n * m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    int m, n; std::cin >> m >> n;
    std::vector<std::vector<int>> arr(m, std::vector<int>(1+n));
    for (int r = 0; r < m; ++r) {
        for (int c = 1; c <= n; ++c) {
            std::cin >> arr[r][c];
        }
    }
    
    for (int c = 1; c <= n; ++c) {
        int s = 0;        
        for (int r = 0; r < m; ++r) {
            if (s <= arr[r][c-1]) {
                s = arr[r][c-1];
            }
            s += arr[r][c];
            arr[r][c] = s;
        }
    }
    for (int r = 0; r < m; ++r) {
        std::cout << arr[r][n] << ' ';
    }
    return 0;
}