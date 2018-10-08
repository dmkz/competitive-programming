/*
    Problem: 367A. Sereja and Algorithm
    
    Solution: prefix sums, O(n + q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    std::string s; std::cin >> s;
    s = '?' + s;
    int n = (int)s.size();
    std::vector<int> nx(n), ny(n), nz(n);
    for (int i = 1; i < n; ++i) {
        nx[i] = nx[i-1] + (s[i] == 'x');
        ny[i] = ny[i-1] + (s[i] == 'y');
        nz[i] = nz[i-1] + (s[i] == 'z');
    }
    int nQ; std::cin >> nQ;
    while (nQ--) {
        int l, r; std::cin >> l >> r;
        int x = nx[r] - nx[l-1];
        int y = ny[r] - ny[l-1];
        int z = nz[r] - nz[l-1];
        std::cout << (r-l+1 < 3 || std::max({x,y,z})-std::min({x,y,z}) <= 1 ? "YES" : "NO") << '\n';
    }
    return 0;
}