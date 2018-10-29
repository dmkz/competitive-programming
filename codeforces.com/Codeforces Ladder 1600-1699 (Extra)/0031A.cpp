/*
    Problem: 31A. Worms Evolution
    
    Solution: brute force, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        bool flag = false;
        for (int i = 0; !flag && i < n; ++i) {
            for (int j = 0; !flag && j < n; ++j) {
                for (int k = j+1; !flag && k < n; ++k) {
                    if (arr[i] == arr[j] + arr[k]) {
                        flag = true;
                        std::cout << i+1 << ' ' << j+1 << ' ' << k+1 << std::endl;
                    }
                }
            }
        }
        if (!flag) {
            std::cout << -1 << std::endl;
        }
    }
    return 0;
}