/*
    Problem: 1119E. Pavel and Triangles
    
    Solution: greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<int> a(n);
        for (auto &it : a) {
            std::cin >> it;
        }
        ll carry = 0, answ = 0;
        for (int i = 0; i < n; ++i) {
            int dt = (int)std::min(ll(a[i] / 2), carry);
            a[i] -= 2 * dt;
            carry -= dt;
            answ += dt;
            answ += a[i] / 3;
            a[i] %= 3;
            carry += a[i];
        }
        std::cout << answ << std::endl;
    }
    return 0;
}