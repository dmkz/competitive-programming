#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int n; std::cin >> n;
    std::deque<int> a(n); for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end());
    while (a.size() > 1u) {
        a.pop_back();
        if (a.size() > 1u) {
            a.pop_front();
        }
    }
    std::cout << a.front() << std::endl;
    
    
    return 0;
}