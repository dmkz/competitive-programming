/*
    Problem: 710B. Optimal Point on a Line
    
    Solution: math, sorting, dynamic programming, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) {
        std::cin >> it;
    }
    std::sort(arr.begin(), arr.end());
    ll left = 0, right = 0;
    for (int i = 1; i < n; ++i) {
        right += arr[i] - arr[0];
    }
    ll imin = 0, best = right;
    for (int i = 1; i < n; ++i) {
        ll diff = arr[i] - arr[i-1];
        right -= (n-i) * diff;
        left += i * diff;
        if (left+right < best) {
            best = left + right;
            imin = i;
        }
    }
    std::cout << arr[imin];
    return 0;
}