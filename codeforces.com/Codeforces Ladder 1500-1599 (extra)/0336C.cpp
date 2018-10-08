/*
    Problem: 336C. Vasily the Bear and Sequence
    
    Solution: bitmasks, implementation, O(32*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    
    std::vector<std::vector<bool>> use(32, std::vector<bool>(n));
    std::vector<bool> can(32);
    for (int p = 0; p < 31; ++p) {
        int res = ~0;
        for (int i = 0; i < n; ++i) {
            if (((arr[i] >> p) & 1) == 0) {
                continue;
            }
            res &= arr[i];
            use[p][i] = true;
        }
        if ((res & ((1 << p) - 1)) == 0) {
            can[p] = true;
        }
    }
    for (int p = 30; p >= 0; --p) {
        if (can[p]) {
            std::vector<int> answ;
            for (int i = 0; i < n; ++i) {
                if (use[p][i]) {
                    answ.push_back(arr[i]);
                }
            }
            if (answ.size() > 0u) {
                std::cout << answ.size() << '\n';
                for (auto it : answ) std::cout << it << ' ';
                return 0;
            }
        }
    }
    throw 1;
}