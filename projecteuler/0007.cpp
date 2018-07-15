#include <iostream>
#include <string>
#include <algorithm>

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int main() {
    int steps = 10001, n = 1;
    while (steps--) {
        while (!is_prime(++n));
    }
    std::cout << n;
    return 0;
}