#include <bits/stdc++.h>

typedef long long Int;

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<Int> a(n); for (auto& it : a) std::cin >> it;
    std::vector<Int> s{0}; for (auto& it : a) s.push_back(s.back()+it);
    for (int i = 0; i < q; ++i) {
        Int number; std::cin >> number;
        auto pos = int(std::lower_bound(s.begin(), s.end(), number) - s.begin());
        number -= s[pos-1];
        std::cout << pos << " " << number << "\n";
    }
    return 0;
}