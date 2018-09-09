/*
    Problem: 846A. Curriculum Vitae
    
    Solution: prefix sums, brute force, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; scanf("%d", &n);
    std::vector<int> arr(n);
    for (auto& it : arr) scanf("%d", &it);
    std::vector<int> nZeros{0};
    for (auto& it : arr) nZeros.push_back(nZeros.back() + (it == 0));
    int answ = 0;
    for (int i = 0; i <= n; ++i) {
        answ = std::max(answ, nZeros[i] + (n-i - (nZeros[n] - nZeros[i])));
    }
    printf("%d", answ);
    return 0;
}