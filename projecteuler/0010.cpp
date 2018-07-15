#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main() {
    const int n = 2*1000*1000;
    std::vector<bool> is_prime(1+n, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }
    long long sum = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            sum += i;
        }
    }
    std::cout << sum;
    return 0;
}