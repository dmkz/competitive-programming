#include <iostream>
typedef long long ll;
int main() {
    ll number = 600851475143LL, answ = 1;
    for (ll i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            while (number % i == 0) number /= i;
            answ = i;
        }
    }
    if (number > 1) {
        answ = std::max(answ, number);
    }
    std::cout << answ;
    return 0;
}