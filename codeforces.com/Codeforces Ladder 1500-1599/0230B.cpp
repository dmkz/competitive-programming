/*
    Problem: 230B. T-primes
    Solution: sieve, math, number theory
*/
#include <iostream>
#include <vector>
#include <cmath>

typedef long long ll;

ll dsqrt(ll number) {
    ll root = (ll)std::sqrt(number);
    while (root*root > number)--root;
    while ((root+1)*(root+1) <= number)++root;
    return root;
}

bool solve(ll number, const std::vector<bool>& is_prime) {
    ll root = dsqrt(number);
    return is_prime[root] && root*root == number;
}

int main() {
    // Sieve:
    const int RMAX = (int)1e6;
    std::vector<bool> is_prime(1+RMAX, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= RMAX; ++i) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= RMAX; j += i) {
            is_prime[j] = false;
        }
    }
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    // Queries:
    int n; std::cin >> n;
    while (n--) {
        ll number; std::cin >> number;
        std::cout << (solve(number, is_prime) ? "YES" : "NO") << '\n';
    }

    return 0;
}