/*
    Problem: 702B. Powers of Two
    
    Solution: sorting, binary search, O(n*log(n)*W)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<ll> arr(n);
    
    for (auto& it : arr) {
        std::cin >> it;
    }
    
    std::sort(arr.begin(), arr.end());
    
    ll answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int pow = 1; pow < 32; ++pow) {
            ll item = (ll(1) << pow) - arr[i];
            if (item < arr[i]) continue;
            auto pt = std::equal_range(arr.begin()+i+1, arr.end(), item);
            answer += int(pt.second - pt.first);
        }
    }
    std::cout << answer;
    
    return 0;
}