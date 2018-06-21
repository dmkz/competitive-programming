#include <iostream>

int main() {
    int n, mod;
    std::cin >> n >> mod;
    int answ = 2 % mod;
    for (int i = 1; i <= n; ++i) {
        answ = answ * answ % mod;
    }
    std::cout << answ;
    return 0;
}