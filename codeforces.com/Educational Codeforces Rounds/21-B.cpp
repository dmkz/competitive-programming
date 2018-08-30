/*
    Problem: 808B. Average Sleep Time
    
    Solution: prefix sums, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>

typedef long long ll;

int main() {
    int n, k; std::cin >> n >> k;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::vector<ll> sum(n-k+1);
    for (int i = 0; i < k; ++i) {
        sum[0] += arr[i];
    }
    for (int i = 1; i + k - 1 < n; ++i) {
        sum[i] = sum[i-1] + arr[i + k - 1] - arr[i-1];
    }
    std::cout << std::fixed << std::setprecision(6) << 1.0L*std::accumulate(sum.begin(), sum.end(), ll(0)) / (int)sum.size();
    return 0;
}