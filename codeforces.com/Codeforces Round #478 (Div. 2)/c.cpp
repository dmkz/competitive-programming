#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-result"

typedef int64_t Int;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<Int> a(n); for (auto& it : a) std::cin >> it;
    std::vector<Int> pref{0};
    for (auto it : a) pref.push_back(pref.back()+it);
    
    Int cur = 0;
    for (int i = 0; i < q; ++i) {
        Int k; std::cin >> k;
        cur += k;
        auto it = std::upper_bound(pref.begin(), pref.end(), cur);
        Int answ = Int(pref.end() - it);
        if (answ == 0) {
            cur = 0;
            answ = n;
        }
        std::cout << answ << "\n";
    }
    
    
    
    return 0;
}