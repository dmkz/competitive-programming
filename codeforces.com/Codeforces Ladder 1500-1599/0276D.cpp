/*
    Problem: 276D. Little Girl and Maximum XOR
    Solution: greedy, bitmasks, math
*/
#include <iostream>

typedef long long ll;

int main() {
    ll l, r; std::cin >> l >> r;
    if (l == r) {
        std::cout << 0;
        return 0;
    }
    for (int i = 60; i >= 0; --i) {
        if (((l >> i) & 1) != ((r >> i) & 1)) {
            std::cout << (ll(1) << (i+1)) - 1;
            return 0;
        }
    }
    throw 1;
}