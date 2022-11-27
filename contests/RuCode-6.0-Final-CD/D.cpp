#include <bits/stdc++.h>

double solve(int k, int t) {
    return (double(t) - 0.5) / k;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int q; std::cin >> q;
    double max = 0;
    for (size_t i=0; i<q; ++i) {
        int k, t;
        std::cin >> k >> t;
        max = std::max(max, solve(k, t));
    }
    std::cout<<std::fixed<<std::setprecision(4)<<max;

    return 0;
}
