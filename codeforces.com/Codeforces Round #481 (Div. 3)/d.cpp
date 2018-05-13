#include <bits/stdc++.h>

int main() {
    int n; std::cin >> n;
    std::vector<int> a(n); for (auto& it : a) std::cin >> it;
    if (n <= 2) {
        std::cout << 0 << std::endl; 
        return 0;
    }
    const int INF = (int)1e9;
    int best = INF;
    for (int d0 = -1; d0 <= 1; ++d0) {
        for (int d1 = -1; d1 <= 1; ++d1) {
            int sum = std::abs(d0)+std::abs(d1);
            int diff = a[1] + d1 - (a[0] + d0);
            int prev = a[1] + d1;
            for (int i = 2; i < n; ++i) {
                int curr = prev + diff;
                if (std::abs(a[i] - curr) > 1) {
                    sum = INF;
                    break;
                } else {
                    sum += std::abs(a[i]-curr);
                    prev = curr;
                }
            }
            best = std::min(sum, best);
        }
    }
    std::cout << (best == INF ? -1 : best) << std::endl;
    return 0;
}