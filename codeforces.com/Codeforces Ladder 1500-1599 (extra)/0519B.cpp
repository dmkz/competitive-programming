/*
    Problem: 519B. A and B and Compilation Errors
    
    Solution: sorting, set_difference, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> a(n), b(n-1), c(n-2);
    for (auto& it : a) std::cin >> it;
    for (auto& it : b) std::cin >> it;
    for (auto& it : c) std::cin >> it;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());
    {
        std::vector<int> temp;
        std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(temp));
        for (auto& it : temp) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    {
        std::vector<int> temp;
        std::set_difference(b.begin(), b.end(), c.begin(), c.end(), std::back_inserter(temp));
        for (auto& it : temp) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}