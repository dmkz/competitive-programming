/*
    Problem: C. inn
    Solution: binary search on answer, O(t*log(n))
*/
#include <bits/stdc++.h>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    ll b, c;
    while (std::cin >> b >> c, b + c) {
        ll low = 0, high = INT_MAX;
        while (high - low > 1) {
            ll x = (low + high) / 2;
            if (- (x+1) * b + x * c > 0) { high = x; }
            else { low = x; }
        }
        std::cout << high << '\n';
    }
    return 0;
}