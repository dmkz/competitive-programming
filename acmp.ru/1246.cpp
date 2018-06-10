#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cassert>

typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b = 1, c, d = 1;
    char buf1[30], buf2[30], op;
    scanf("%s %c %s", buf1, &op, buf2);
    sscanf(buf1, "%d/%d", &a, &b);
    sscanf(buf2, "%d/%d", &c, &d);
    ll p = 0, q = 1;
    if (op == '*') {
        p = ll(a) * c;
        q = ll(b) * d;
    } else if (op == '/') {
        p = ll(a) * d;
        q = ll(b) * c;
    } else if (op == '-') {
        p = ll(a) * d - ll(b) * c;
        q = ll(b) * d;
    } else {
        assert(op == '+');
        p = ll(a) * d + ll(b) * c;
        q = ll(b) * d;
    }
    ll gcd = ::gcd(std::abs(p), std::abs(q));
    assert(p % gcd == 0);
    assert(q % gcd == 0);
    p /= gcd;
    q /= gcd;
    if (q < 0) {
        p *= -1;
        q *= -1;
    }
    std::cout << p;
    if (p != 0 && q != 1) {
        std::cout << '/' << q;
    }
    return 0;
}