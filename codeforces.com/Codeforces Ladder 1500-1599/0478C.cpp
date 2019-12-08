/*
    Problem: 478C. Table Decorations
    Solution: greedy, O(1)
*/
#include <iostream>
#include <algorithm>

typedef long long ll;

int main() {
    ll a, b, c; std::cin >> a >> b >> c;
    if (a > b) std::swap(a, b);
    if (a > c) std::swap(a, c);
    if (b > c) std::swap(b, c);
    if (c >= 2 * (a + b)) {
        std::cout << a + b;
    } else {
        std::cout << (a + b + c) / 3;
    }
    return 0;
}