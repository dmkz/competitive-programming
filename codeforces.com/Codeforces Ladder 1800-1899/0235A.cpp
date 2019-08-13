/*
    Problem: 235A. LCM Challenge
    Solution: lcm, number theory, math, brute force
*/
#include <bits/stdc++.h>
typedef long long ll;
ll naive(int a, int b) {
    ll max = 1;
    for (ll i = a; i <= b; i++) {
        for (ll j = a; j <= b; j++) {
            const ll lcm = std::lcm(i,j);
            for (ll k = a; k <= b; k++) {
                max = std::max(max, std::lcm(lcm, k));
            }
        }
    }
    return max;
}
int main() {
    for (int n; std::cin >> n; std::cout << naive(std::max(1, n-100), n) << std::endl);
    return 0;
}