/*
    Problem: 485B. Valuable Resources
    
    Solution: geometry, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
const int INF = (int)1e9+1;
int main() {
    int x_min = INF, x_max = -INF, y_min=INF, y_max=-INF;
    int n; std::cin >> n;
    while (n--) {
        int x, y;
        std::cin >> x >> y;
        x_max = std::max(x, x_max);
        y_max = std::max(y, y_max);
        x_min = std::min(x, x_min);
        y_min = std::min(y, y_min);
    }
    int side = std::max(y_max-y_min, x_max-x_min);
    std::cout << 1LL * side * side;
    return 0;
}