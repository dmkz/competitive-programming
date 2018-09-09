/*
    Problem: 792A. New Bus Route
    
    Solution: sorting, implementation, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<ll> a(n);
    for (auto& it : a) std::cin >> it;
    std::sort(a.begin(), a.end());
    
    ll min = (ll)1e18, count = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] - a[i-1] < min) {
            min = a[i] - a[i-1]; count = 1;
        } else if (a[i] - a[i-1] == min) {
            ++count;
        }
    }
    std::cout << min << ' ' << count;
    return 0;
}