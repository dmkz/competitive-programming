/*
    Problem: 678C. Joty and Chocolate
    
    Solution: gcd, lcm, number theory, combinatorics, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

inline ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

int main() {
    ll n, a, b, p, q;
    std::cin >> n >> a >> b >> p >> q;
    ll answ = (n / a - n / lcm(a, b)) * p;
    answ += (n / b - n / lcm(a, b)) * q;
    answ += n / lcm(a,b) * std::max(p, q);
    std::cout << answ;
    return 0;
}