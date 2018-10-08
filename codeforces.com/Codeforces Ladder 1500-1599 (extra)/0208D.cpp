/*
    Problem: 208D. Prizes, Prizes, more Prizes
    
    Solution: implementation, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
typedef long long ll;
int main() {
    int n; std::cin >> n;
    std::vector<int> seq(n);
    for (auto& it : seq) std::cin >> it;
    std::vector<ll> cnt(5), cost(5);
    for (auto& it : cost) {
        std::cin >> it;
    }
    ll rem = 0;
    for (auto& it : seq) {
        rem += it;
        for (int i = 4; i >= 0; --i) {
            cnt[i] += rem / cost[i];
            rem %= cost[i];
        }
    }
    for (auto& it : cnt) {
        std::cout << it << ' ';
    }
    std::cout << '\n' << rem;
    return 0;
}