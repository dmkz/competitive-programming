/*
    Problem: 483B. Friends and Presents
    Solution: binary search, math
*/
#include <iostream>
#include <algorithm>

typedef long long ll;

int main() {
    ll n1, n2, x, y;
    std::cin >> n1 >> n2 >> x >> y;
    ll low = n1+n2-1, high = (ll)1e18L;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        ll to2 = std::max(ll(0),n2 - (mid / x - mid / (x*y)));
        ll to1 = std::max(ll(0),n1 - (mid / y - mid / (x*y)));
        ll have = mid - mid / x - mid / y + mid / (x*y);
        bool flag = have >= to1 + to2;
        if (flag) {
            high = mid;
        } else low = mid;
    }
    std::cout << high;
    return 0;
}