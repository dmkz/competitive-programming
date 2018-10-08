/*
    Problem: 468A. 24 Game
    
    Solution: constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

int main() {
    int n; std::cin >> n;
    if (n < 4) {std::cout << "NO"; return 0;}
    std::cout << "YES\n";
    std::vector<int> cnt(1+100000);
    for (int i = 1; i <= n; ++i) cnt[i] = 1;
    for (int i = n-1; i >= 5; i -= 2) {
        std::cout << i+1 << " - " << i << " = " << 1 << '\n';
        cnt[i]--; cnt[i+1]--; cnt[1]++;
    }
    if (cnt[5] > 0) {
        std::cout << 5 << " - " << 1 << " = " << 4 << '\n';
        cnt[5]--;
        cnt[1]--;
        cnt[4]++;
        std::cout << 4 << " - " << 2 << " = " << 2 << '\n';
        cnt[4]--;
    }
    std::vector<int> temp;
    for (int i = 1; i <= n; ++i) {
        while (cnt[i]--) {temp.push_back(i);}
    }
    int prod = temp[0];
    for (int i = 1; i < (int)temp.size(); ++i) {
        std::cout << prod << " * " << temp[i] << " = " << prod * temp[i] << "\n";
        prod *= temp[i];
    }
    assert(prod == 24);
    return 0;
}