/*
    Problem: 414A. Mashmokh and Numbers
    
    Solution: constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    int n, k;
    std::cin >> n >> k;
    // n / 2 pairs
    // (n / 2 - 1) + k - (n / 2 + 1)
    if (n == 1 && k == 0) {
        std::cout << 1; return 0;
    }
    if (n == 1 && k == 1) {
        std::cout << -1; return 0;
    }
    int rem = k - (n / 2 - 1);
    if (rem < 1 || rem > k) { std::cout << -1; return 0; }
    std::vector<int> answ{rem, 2*rem};
    std::map<int, bool> used;
    used[rem] = used[2*rem] = true;
    int s = 1;
    while (answ.size() < n) {
        while (used[s] || used[s+1]) s++;
        used[s] = used[s+1] = true;
        answ.push_back(s);
        answ.push_back(s+1);
    }
    if (answ.size() > n) answ.pop_back();
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}