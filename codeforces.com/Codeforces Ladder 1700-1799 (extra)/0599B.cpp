/*
    Problem: 599B. Spongebob and Joke
    
    Solution: math, constructive, permutation, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        std::vector<int> f(1+n), b(1+m);
        for (int i = 1; i <= n; ++i) { std::cin >> f[i]; }
        for (int i = 1; i <= m; ++i) { std::cin >> b[i]; }
        // define: g(x) = f^(-1)
        // a[i] = g[b[i]] =
        std::vector<std::vector<int>> g(1+n);
        for (int i = 1; i <= n; ++i) {
            g[f[i]].push_back(i);
        }
        std::vector<int> a(1+m);
        int nSolutions = 1;
        for (int i = 1; nSolutions >= 1 && i <= m; ++i) {
            auto &to = g[b[i]];
            if (to.empty()) {
                nSolutions = 0;
            } else if (to.size() == 1u) {
                a[i] = to.front();
            } else {
                nSolutions = 2;
            }
        }
        if (nSolutions == 0) {
            std::cout << "Impossible\n";
        } else if (nSolutions == 2) {
            std::cout << "Ambiguity\n";
        } else {
            std::cout << "Possible\n";
            for (int i = 1; i <= m; ++i) {
                std::cout << a[i] << " ";
            }
            std::cout << std::endl;
        }
    }
    return 0;
}