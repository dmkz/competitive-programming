/*
    Problem: 535C. Tavas and Karafs
    
    Solution: math, binary search, O(n log(m*t))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

ll sum(ll A, ll B, ll r) {
    return A * r + r * (r-1) / 2 * B;
}

ll sum(ll A, ll B, ll l, ll r) {
    return sum(A,B,r)-sum(A,B,l-1);
}

ll number(ll A, ll B, ll index) {
    return A + (index-1) * B;
}

ll check(ll A, ll B, ll left, ll times, ll max, ll cnt) {
    return sum(A,B,left,left+cnt-1) <= times * max && number(A,B,left+cnt-1) <= times;
}

ll solve(ll A, ll B, ll left, ll times, ll max) {
    ll len = 0; int pow = 0;
    while (pow >= 0) {
        if (!check(A,B,left,times,max,len+(ll(1) << pow))) {
            --pow; continue;
        } else {
            len += (ll(1) << pow);
            pow++;
        }
    }
    return len == 0 ? -1 : left+len-1;
}

int main() {
    ll A, B, q;
    std::cin >> A >> B >> q;
    while (q--) {
        ll left, times, max;
        std::cin >> left >> times >> max;
        std::cout << solve(A, B, left, times, max) << '\n';
    }
    return 0;
}