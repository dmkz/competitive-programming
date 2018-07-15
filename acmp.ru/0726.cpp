/*
    "Остатки": система диофантовых уравнений, расширенный алгоритм Евклида, O(log(n))
*/

#include <iostream>
#include <vector>
#include <cassert>

typedef long long ll;

bool gcd(ll a, ll b, ll c, ll& x, ll& y) {
    if (a < b) {
        return gcd(b, a, c, y, x);
    }
    if (c == 0) {
        x = b;
        y = -a;
        return true;
    }
    if (b == 0) {
        x = c;
        y = 0;
        return true;
    }
    std::vector<ll> r{a, b}, q;
    while (b != 0 && a % b != 0) {
        q.push_back(a / b);
        r.push_back(a % b);
        a = b;
        b = r.back();
    }
    assert(r.back() != 0);
    if (c % r.back() != 0) {
        return false;
    }
    
    x = 0, y = 1;
    while (!q.empty()) {
        ll z = -q.back() * y + x;
        x = y;
        y = z;
        q.pop_back();
    }
    x *= c / r.back();
    y *= c / r.back();
    return true;
}

int main() {
    bool flag = true;
    ll a1, b1, c1, x1, y1;
    std::cin >> a1 >> b1 >> c1;
    
    b1 %= c1;
    flag = gcd(a1, -c1, b1, x1, y1);
    if (!flag) {
        std::cout << "NO";
        return 0;
    }
    assert(a1 * x1 - c1 * y1 == b1);
    
    ll a2, b2, c2, x2, y2;
    std::cin >> a2 >> b2 >> c2;
    
    b2 %= c2;
    flag = gcd(a2, -c2, b2, x2, y2);
    if (!flag) {
        std::cout << "NO";
        return 0;
    }
    assert(a2 * x2 - c2 * y2 == b2);
    
    ll x, y;
    flag = gcd(c1, c2, x2-x1, x, y);
    if (!flag) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES";
    return 0;
}