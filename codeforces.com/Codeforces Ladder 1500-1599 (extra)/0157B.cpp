/*
    Problem: 157B. Trace
    
    Solution: geometry, circles, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>

const double PI = std::acos(-1.0);

int main() {
    std::cout << std::fixed << std::setprecision(4);
    int n; std::cin >> n;
    std::vector<int> r(n);
    for (auto& it : r) std::cin >> it;
    std::sort(r.begin(), r.end(), std::greater<int>());
    int sum = 0;
    for (int i = 0; i < (int)r.size(); ++i) {
        sum += i % 2 == 0 ? r[i]*r[i] : -r[i]*r[i];
    }
    std::cout << sum * PI;
    return 0;
}