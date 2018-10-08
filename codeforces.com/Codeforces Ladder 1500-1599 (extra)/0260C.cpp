/*
    Problem: 260C. Balls and Boxes
    
    Solution: math, implementation, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, x; std::cin >> n >> x; --x;
    std::vector<ll> arr(n);
    for (auto& it : arr) std::cin >> it;
    ll min = *std::min_element(arr.begin(), arr.end());
    ll elem = min * n;
    for (auto& it : arr) it -= min;
    while (arr[x] != 0) {
        elem++;
        arr[x]--;
        x = (x-1+n) % n;
    }
    arr[x] += elem;
    for (auto& it : arr) std::cout << it << ' ';
    return 0;
}