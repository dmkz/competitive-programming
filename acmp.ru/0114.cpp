#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

typedef long long ll;

int main() {
    ll n, k; std::cin >> n >> k; assert(n > 1);
    
    std::vector<ll> count(1+n, 0);
    count[1] = (k-1);
    count[2] = (k-1) * k;
    for (int i = 3; i <= n; ++i) {
        count[i] = (k-1) * (count[i-1] + count[i-2]);
    }
    std::cout << count[n] << std::endl;
    return 0;
}