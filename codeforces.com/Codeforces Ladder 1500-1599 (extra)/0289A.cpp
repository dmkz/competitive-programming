/*
    Problem: 289A. Polo the Penguin and Segments
    
    Solution: implementation, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <algorithm>
typedef long long ll;
int main() {
    int n, k; std::cin >> n >> k;
    int s = 0;
    for (int i = 0; i < n; ++i) {
        int l, r; std::cin >> l >> r;
        s += (r - l + 1);
    }
    std::cout << (s + k - 1) / k * k - s;
    return 0;
}