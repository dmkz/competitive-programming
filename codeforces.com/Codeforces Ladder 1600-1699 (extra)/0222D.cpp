/*
    Problem: 222D. Olympiad
    
    Solution: greedy, sorting, set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
    int n, x;
    while (std::cin >> n >> x) {
        std::vector<int> a(n), b(n);
        for (auto& it : a) { std::cin >> it; }
        for (auto& it : b) { std::cin >> it; it = x - it;}
        std::multiset<int> set;
        for (auto& it : a) { set.insert(it); }
        std::sort(b.begin(), b.end());
        int answ = 0;
        for (int i = n-1; i >= 0; --i) {
            auto it = set.lower_bound(b[i]);
            if (it == set.end()) {
                continue;
            }
            answ++;
            set.erase(it);
        }
        std::cout << 1 << " " << answ << std::endl;
    }
    return 0;
}