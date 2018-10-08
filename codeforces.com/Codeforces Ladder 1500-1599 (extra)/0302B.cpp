/*
    Problem: 302B. Eugeny and Play List
    
    Solution: prefix sums, two pointers, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> sum{0};
    for (int i = 0; i < n; ++i) {
        int c, t; std::cin >> c >> t;
        sum.push_back(sum.back() + c*t);
    }
    int p = 1;
    while (q--) {
        int v; std::cin >> v;
        while (sum[p] < v) ++p;
        std::cout << p << '\n';
    }
    return 0;
}