/*
    Problem: 557B. Pasha and Tea
    
    Solution: greedy, math, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, w;
    std::cin >> n >> w;
    std::vector<int> arr(2*n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    double max = std::min({1.0*arr[0], arr[n] / 2.0, w / 3.0 / n});
    printf("%0.6f", 3 * n * max);
    return 0;
}