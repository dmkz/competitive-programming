/*
    Problem: 83A. Magical Array
    
    Solution: two pointers, combinatorics, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        int len = 0, last = arr[0]; ll answ = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == last) {
                len++;
            } else {
                answ += ll(len) * (len+1) / 2;
                len = 1;
                last = arr[i];
            }
        }
        answ += ll(len) * (len+1) / 2;
        std::cout << answ << std::endl;
    }
    return 0;
}