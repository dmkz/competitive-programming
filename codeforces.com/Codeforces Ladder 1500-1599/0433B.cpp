/*
    Problem: 433B. Kuriyama Mirai's Stones
    Solution: dynamic programming, prefix sums, sorting
*/
#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

struct PrefSum {

    std::vector<ll> data;
    
    PrefSum(const std::vector<int>& arr) {
        data.push_back(0);
        for (auto& it : arr) data.push_back(data.back() + it);
    }
    
    inline ll operator()(int l, int r) const {
        return data[r+1] - data[l];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& it : a) std::cin >> it;
    auto b = a;
    std::sort(a.begin(), a.end());
    PrefSum s1(b), s2(a);
    int q; std::cin >> q;
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r; --l, --r;
        std::cout << (t == 1 ? s1(l, r) : s2(l, r)) << '\n';
    }
    return 0;
}