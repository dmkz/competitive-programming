#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

typedef long long ll;

// Расстояние от точки p до точек x:
ll dist(ll p, const std::vector<ll>& x) {
    ll sum = 0;
    for (auto& it : x) {
        sum += std::abs(p-it);
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    
    std::vector<ll> x(n);
    for (auto& it : x) {
        int value;
        scanf("%d", &value);
        it = value;
    }
    
    // Тернарный поиск:
    ll l = -2e9, r = 2e9;
    while (r - l > 11) {
        assert(l <= r);
        ll m1 = (6 * l + 5 * r) / 11;
        ll m2 = (5 * l + 6 * r) / 11;
        assert(m1 <= m2);
        ll v1 = dist(m1, x);
        ll v2 = dist(m2, x);
        if (v1 < v2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    // Находим минимум на отрезке [l, r]:
    int min = r, minv = dist(r, x);
    for (int i = r-1; i >= l; --i) {
        int curv = dist(i, x);
        if (curv < minv) {
            min = i;
            minv = curv;
        }
    }
    
    std::cout << min;
    return 0;
}