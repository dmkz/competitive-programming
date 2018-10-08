/*
    Problem: 263B. Squares
    
    Solution: greedy, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, need;
    std::cin >> n >> need; --need;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end(), std::greater<int>());
    if (need >= n) { std::cout << -1; return 0; }
    std::cout << a[need] << ' ' << a[need];
    return 0;
}