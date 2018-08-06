/*
    Problem: 1016E. Rest In The Shades
    
    Solution: geometry, binary search, O(n + q*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>

typedef long double Real;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int y, s, t;
    std::cin >> y >> s >> t;
    
    int n; std::cin >> n;
    
    // Create segments:
    std::vector<int> seg{0};
    for (int i = 0; i < n; ++i) {
        int l, r; std::cin >> l >> r;
        seg.push_back(l);
        seg.push_back(r);
    }
    seg.push_back((int)1e9+1);
    
    // Calculate prefix sum:
    std::vector<int> sum((int)seg.size());
    for (int i = 2; i < (int)seg.size(); ++i) {
        sum[i] = sum[i-1] + (i % 2 ? 0 : seg[i] - seg[i-1]);
    }
    
    // Answer to queries:
    int q; std::cin >> q;
    while (q--) {
        int x1, y1; 
        std::cin >> x1 >> y1;
        int dx = s - x1;
        int dy = y - y1;
        // Intersect lines (x1,y1)-->(s,y) and (x1,y1)-->(t,y) with Ox:
        Real l = x1 - Real(dx) * y1 / dy;
        dx = t - x1;
        Real h = x1 - Real(dx) * y1 / dy;
        Real coeff = std::sqrt((Real(dx) * dx + Real(dy) * dy) / (Real(y1) * y1 + Real(h-x1)*(h-x1)));
        // Binary search by segments:
        int it_l = int(std::upper_bound(seg.begin(), seg.end(), (int)std::floor(l))-seg.begin());
        int it_h = int(std::upper_bound(seg.begin(), seg.end(), (int)std::floor(h))-seg.begin());
        // Calculate intersect length and multiply by coeff:
        Real intersect = sum[it_h] - sum[it_l];        
        if (it_l != it_h) {
            if (it_l % 2 == 0) {
                intersect += seg[it_l] - l;
            }
            if (it_h % 2 == 0) {
                intersect -= seg[it_h] - h;
            }
        } else {
            if (it_l % 2 == 0) {
                intersect += h - l;
            }
        }
        intersect *= coeff;
        // Output answer to query:
        std::cout << std::fixed << std::setprecision(6) << intersect << '\n';
    }
    
    return 0;
}