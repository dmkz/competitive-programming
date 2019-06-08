/*
    Problem: 367C. Sereja and the Arrangement of Numbers
    
    Solution: graphs, euler path, O(m log(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
int main() {
    for (int n, m, tmp; std::cin >> n >> m; ) {
        std::vector<int> w(m);
        for (auto &it : w) { std::cin >> tmp >> it; }
        std::sort(w.begin(),w.end(),std::greater<>());
        int cnt = 1;
        for (int i = cnt+1; i <= m && i <= n; i++) {
            int edges = i * (i-1) / 2;
            edges += (i % 2 ? 1 : i / 2);
            if (edges <= n) { cnt = i; } 
            else { break; }
        }
        w.resize(cnt);
        std::cout << std::accumulate(all(w), 0LL) << std::endl;
    }
    return 0;
}