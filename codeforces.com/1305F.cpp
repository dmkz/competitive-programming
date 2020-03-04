/*
    Problem: 1305F. Kuroni and the Punishment
    Solution: number theory, random, primes, gcd, O(30*log(MAX)*n)
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()

using ll = long long;

const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);

int main() {
    // Input:
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n; std::cin >> n;
    std::vector<ll> a(n);
    for (auto &it : a) std::cin >> it;
    std::vector<ll> primes{2};
    // Pick random primes that we will check as gcd:
    std::uniform_int_distribution<int> dist(0, n-1);
    for (int iter = 0; iter < 30; iter++) {
        const auto item = a[dist(gen)];
        for (ll x : {item-1,item,item+1}) {
            for (int i = 2; i * 1LL * i <= x; i++) {
                if (x % i == 0) {
                    primes.push_back(i);
                    x /= i;
                    while (x % i == 0) x /= i;
                }
            }
            if (x > 1) primes.push_back(x);
        }
    }
    std::sort(all(primes));
    primes.erase(std::unique(all(primes)),primes.end());
    // check each prime:
    ll answ = n;
    for (ll p : primes) {
        ll curr = 0;
        for (ll x : a) {
            ll rem = x % p;
            ll next = x + p - rem;
            ll prev = x - rem;
            ll min = next - x;
            if (prev > 0) {
                min = std::min(min, x - prev);
            }
            curr += min;
            if (curr > answ) {
                break;
            }
        }
        answ = std::min(answ, curr);
    }
    std::cout << answ << std::endl;
    return 0;
}