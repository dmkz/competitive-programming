#include <bits/stdc++.h>
int main() {
    int n; std::cin >> n;
    if (n <= 3) std::cout << "-1\n";
    else {
        std::vector<std::pair<int,int>> edges;
        edges.emplace_back(1,2);
        edges.emplace_back(1,3);
        edges.emplace_back(2,3);
        edges.emplace_back(4,2);
        edges.emplace_back(4,3);
        for (int i = 5; i <= n; i++) {
            edges.emplace_back(i-1,i);
        }
        std::cout << edges.size() << '\n';
        for (const auto &[a,b] : edges)
            std::cout << a << ' ' << b << '\n';
    }
    return 0;
}