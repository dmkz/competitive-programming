#include <iostream>
#include <string>
#include <algorithm>

inline int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int answ = 1;
    for (int i = 1; i <= 20; ++i) {
        answ = lcm(answ, i);
    }
    std::cout << answ;
    return 0;
}