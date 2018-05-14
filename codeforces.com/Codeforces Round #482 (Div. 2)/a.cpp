#include <bits/stdc++.h>

typedef long long Int;

int main() {
    Int n; std::cin >> n;
    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    if ((n+1) % 2 == 0) {
        std::cout << (n + 1) / 2 << std::endl;
        return 0;
    }
    std::cout << n+1 << std::endl;
    return 0;
}