/*
    Problem: 231D. Magic Box
    
    Solution: geometry, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
int main() {
    int x, y, z, sx, sy, sz;
    std::cin >> x >> y >> z;
    std::cin >> sx >> sy >> sz;
    std::vector<int> a(6);
    int res = 0;
    for (auto& it : a) { std::cin >> it; res += it; }
    if (y >=  0) res -= a[0];
    if (y <= sy) res -= a[1];
    if (z >=  0) res -= a[2];
    if (z <= sz) res -= a[3];
    if (x >=  0) res -= a[4];
    if (x <= sx) res -= a[5];
    std::cout << res;
    return 0;
}