#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-result"


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    int n; std::cin >> n;
    std::set<std::string> set;
    for (int i = 0; i < n; ++i) {
        std::string s; std::cin >> s;
        std::sort(s.begin(), s.end());
        s.erase(std::unique(s.begin(), s.end()), s.end());
        set.insert(s);
    }
    std::cout << set.size() << std::endl;
    return 0;
}