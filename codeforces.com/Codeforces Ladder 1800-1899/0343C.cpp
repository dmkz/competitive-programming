/*
    Problem: 343C. Read Time
    Solution: binary search, greedy, O((n+m) * log(1e18))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using ll = long long;
using vl = std::vector<ll>;
int main() {
    for (int n, m; std::cin >> n >> m; ) {
        vl a(n), b(m), tmp(m);
        for (auto &it : a) std::cin >> it;
        for (auto &it : b) std::cin >> it;
        ll low = -1, high = (ll)1e18L;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            tmp = b;
            for (int i = n-1; isz(tmp) && i >= 0; i--) {
                int last = isz(tmp);
                while (last-1 >= 0) {
                    ll min = std::abs(tmp.back() - tmp[last-1]);
                    min += std::min(std::abs(a[i] - tmp.back()),std::abs(a[i] - tmp[last-1]));
                    if (min <= mid) {
                        last--;
                    } else {
                        break;
                    }
                }
                tmp.erase(tmp.begin()+last, tmp.end());
            }
            if (isz(tmp)) { low = mid; }
            else { high = mid; }
        }
        std::cout << high << std::endl;
    }
    return 0;
}