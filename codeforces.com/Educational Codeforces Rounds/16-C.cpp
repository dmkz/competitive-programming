/*
    Problem: 710C. Magic Odd Square
    
    Solution: math, constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    int n; std::cin >> n;
    std::vector<std::vector<int>> answ(n, std::vector<int>(n));
    std::vector<int> odd,even;
    for (int i = 1; i <= n * n; ++i) {
        if (i % 2 == 0) even.push_back(i); else odd.push_back(i);
    }
    for (int i = 0; i < n / 2; ++i) {
        for (int j = n / 2-i; j <= n / 2 + i; ++j) {
            assert(!odd.empty());
            answ[i][j] = odd.back();
            odd.pop_back();
            assert(!odd.empty());
            answ[n-i-1][j] = odd.back();
            odd.pop_back();
        }
    }
    for (int j = 0; j < n; ++j) {
        assert(!odd.empty());
        answ[n/2][j] = odd.back();
        odd.pop_back();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (answ[i][j] == 0) {
                assert(!even.empty());
                answ[i][j] = even.back(); 
                even.pop_back();
            }
            std::cout << answ[i][j] << ' ';
        }
        std::cout << '\n';
    }
    
    return 0;
}