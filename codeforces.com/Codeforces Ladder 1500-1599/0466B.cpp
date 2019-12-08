/*
    Problem: 466B. Wonder Room
    Solution: brute force, math
*/
#include <iostream>
#include <algorithm>

typedef long long ll;

void solve(ll x, ll y, ll n, ll& x_opt, ll& y_opt) {
    if (x > y) {
        solve(y, x, n, y_opt, x_opt);
        return;
    }
    
    // x - минимальная сторона
    // y - максимальная сторона
    x_opt = x;
    y_opt = y+(6 * n - x * y + x - 1) / x;
    while (x * x <= 6 * n) {
        auto y_temp = y + (6 * n - x * y + x - 1) / x;
        if (x * y_temp < x_opt * y_opt && x * y_temp >= 6 * n) {
            x_opt = x;
            y_opt = y_temp;
        }
        ++x;
    }
}

int main() {
    
    ll x, y, n;
    std::cin >> n >> x >> y;
    
    if (x*y >= 6*n) {
        std::cout << x * y << '\n' << x << ' ' << y;
        return 0;
    }
    
    ll x_opt, y_opt;
    solve(x,y,n,x_opt,y_opt);
    std::cout << x_opt*y_opt << '\n' << x_opt << ' ' << y_opt;
    return 0;
}