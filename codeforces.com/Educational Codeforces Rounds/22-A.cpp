/*
    Problem: 813A. The Contest
    
    Solution: implementation, math, O(m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
const int INF = (int)1e9+1;
typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    ll s = 0;
    for (int i = 0; i < n; ++i) { 
        int v; std::cin >> v; s += v;
    }
    int m; std::cin >> m;
    int min = INF;
    while (m--) {
        int l, r; std::cin >> l >> r;
        if (l >= s) {
            min = std::min(min, l);
        } else if (l <= s && s <= r) {
            min = std::min(min, (int)s);
        }
    }
    if (min == INF) min = -1;
    std::cout << min;
    return 0;
}