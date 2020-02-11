/*
    Problem: 1299B. Aerodynamic
    Solution: math, geometry, convex polygon, O(n)
*/
#include <bits/stdc++.h>
using pii = std::pair<int,int>;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    if (n % 2 == 1) { std::cout << "NO\n"; return 0; }
    std::vector<int> x(n), y(n);
    pii mid; bool was = false, ok = true;
    for (int i = 0, j; i < n; i++) {
        std::cin >> x[i] >> y[i];
        if ((j = i - n / 2) >= 0) {
            pii tmp{x[j] + x[i], y[j] + y[i]};
            if (!was) mid = tmp, was = true;
            ok &= mid == tmp;
        }
    }
    std::cout << (ok ? "YES\n" : "NO\n");
    return 0;
}