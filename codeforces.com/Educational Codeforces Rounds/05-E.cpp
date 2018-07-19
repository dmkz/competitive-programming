/*
    Problem: 616E. Sum of Remainders
    
    Solution: math, number theory, implementation, O(sqrt(n))
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

const ll MOD = (ll)(1e9)+7;

inline ll mod(ll n) {
    return n >= 0 ? n % MOD : MOD - (-n) % MOD;
}

inline ll sum(ll a, ll b) {
// Sum of a + (a+1) + (a+2) + ... + (b-1) + b:
    ll first = mod(mod(a+b) * mod(b-a+1));
    ll second = mod(first * ((MOD+1)/2));
    return b < a ? 0 : second;
}

ll solve(ll n, ll m) {
// sum n % k, where k = 1 to m equal n * m - sum(n / k * k), k = 1 to m
    ll answ = mod(mod(n) * mod(m));

// Sum where k <= sqrt(n):
    ll max = 1;
    for (ll k = 1; k <= m && k * k <= n; ++k) {
        answ = mod(answ-mod(mod(n / k) * k));
        max = k;
    }
    
// Sum where n / k <= sqrt(n):    
    for (ll t = 1; t * t <= n; ++t) {
        // Get k_min and k_max for n / k == t, k_min <= k <= k_max
        ll k_max = std::min(n / t, m);
        ll k_min = (n + t + 1) / (t + 1);
        
        // Calculate answ -= t * (k_min + (k_min+1) + ... + (k_max-1) + k_max):
        answ = mod(answ-mod(t*sum(std::max(max+1, k_min), k_max)));
        
        // Break if collision with previous cycle:
        if (k_min <= max) {
            break;
        }
    }
    return answ;    
}

int main() {
    ll n, m;
    std::cin >> n >> m;
    std::cout << solve(n, m);
    return 0;
}