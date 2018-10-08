/*
    Problem: 274A. k-Multiple Free Set
    
    Solution: greedy, implementation, std::set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <set>
typedef long long ll;
int main() {
    int n, k;
    std::cin >> n >> k;
    if (k == 1) {
        std::cout << n; return 0;
    }
    std::set<ll> set;
    for (int i = 0; i < n; ++i) {
        int v; std::cin >> v;
        set.insert(v);
    }
    for (auto& it : set) {
        set.erase(it * k);
    }
    std::cout << set.size();
    return 0;
}