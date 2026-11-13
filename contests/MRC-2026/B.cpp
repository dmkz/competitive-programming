#include <bits/stdc++.h>
#include <bits/extc++.h>
int32_t main() {
    int64_t n; std::cin >> n;
    if (n == 1) std::cout << "1\n";
    else if (n == 3) {
        // прямая линия XXX и полуквадрат вида XX
        //                                     X.
        std::cout << "2\n";
    } else {
        // прямая линия или квадрат
        int64_t root = (int64_t)std::sqrtl(n);
        std::cout << 1 + (root * root == n) << "\n";
    }
}
