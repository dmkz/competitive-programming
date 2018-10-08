/*
    Problem: 317A. Perfect Pair
    
    Solution: greedy, math, number theory, O(log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
typedef long long ll;
ll solve(ll x, ll y, ll m) {
    if (x < y) return solve(y, x, m);
    if (x >= m || y >= m) return  0;
    if (x <= 0) return -1;
    ll k = std::max(ll(1), (x - y + x - 1) / x);
    return solve(x, k*x+y, m)+k;
}
int main() {
    ll x, y, m;
    std::cin >> x >> y >> m;
    std::cout << solve(x,y,m);
    return 0;
}