/*
    Problem: 321A. Ciel and Robot
    
    Solution: brute force, geometry, math, equations, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::vector<int> dx(256), dy(256);
    dx['U'] =  0; dy['U'] =  1;
    dx['D'] =  0; dy['D'] = -1;
    dx['L'] = -1; dy['L'] =  0;
    dx['R'] = +1; dy['R'] =  0;
    ll tx, ty;
    std::string s;
    while (std::cin >> tx >> ty >> s) {
        ll DX = 0, DY = 0, cx = 0, cy = 0;
        for (auto it : s) {
            DX += dx[it];
            DY += dy[it];
        }
        bool ok = false;
        s.push_back('-');
        for (auto it : s) {
            // DX * k + cx == tx
            // DY * k + cy == ty
            ll k = 0;
            if (DX != 0) {
                k = (tx - cx) / DX;
            } else if (DY != 0) {
                k = (ty - cy) / DY;
            }
            k = std::max(ll(0), k);
            ok = ok || (DY * k + cy == ty && DX * k + cx == tx);
            cx += dx[it];
            cy += dy[it];
        }
        std::cout << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}