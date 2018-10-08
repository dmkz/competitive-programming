/*
    Problem: 625A. Guest From the Past
    
    Solution: number theory, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

ll solve(ll a, ll b, ll c, ll s) {
    if (a <= b - c) {
        return s / a;
    } else {
        ll ret = (s - c) / (b-c);
        if (ret == 0) {
            return s / a;
        }
        ll c2 = ret * (b-c)+c;
        return std::max({s/a,ret,ret+(s-c2+c)/a,(ret-1)+(s-c2+b)/a});
    }
}

int main() {
    ll s, a, b, c; std::cin >> s >> a >> b >> c;
    std::cout << solve(a,b,c,s);
    return 0;
}