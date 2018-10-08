/*
    Problem: 507C. Guess Your Way Out!
    
    Solution: trees, implementation, math, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
typedef long long ll;
ll solve(ll height, ll leaf, bool isLeft) {
    if (height == 0) {
        return 0;
    }
    bool inLeft = leaf <= (ll(1) << (height-1));
    if (!inLeft) {
        leaf -= (ll(1) << (height-1));
    }
    if (isLeft != inLeft) {
        return (ll(1) << (height)) + solve(height-1, leaf, isLeft);
    } else {
        return 1 + solve(height-1, leaf, !isLeft);
    }
}
int main() {
    ll h, n;
    while (std::cin >> h >> n) {
        std::cout << solve(h, n, 1) << std::endl;
    }
    return 0;
}