/*
    Problem: 1188B. Count Pairs
    Solution: math, number theory, O(n log(n))
*/
#include <bits/stdc++.h>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n,p,k; 
    while (std::cin >> n >> p >> k) {
        // a[i]^4-a[j]^4=k*(a[i]-a[j])
        // a[i]^4-k*a[i] == a[j]^4-k*a[j]
        std::map<int,int> cnt;
        for (int i = 0, v; i < n; i++) {
            std::cin >> v;
            v = int(v * (1LL*v*v % p * v % p - k + p) % p);
            cnt[v]++;
        }
        ll answ = 0;
        for (const auto& it : cnt) {
            answ += it.second * 1LL * (it.second-1) / 2;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}