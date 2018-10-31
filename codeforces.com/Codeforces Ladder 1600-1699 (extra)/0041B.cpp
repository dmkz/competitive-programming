/*
    Problem: 41B. Martian Dollar
    
    Solution: greedy, prefix sums, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = (int)1e9;

int main() {
    int n, sum;
    while (std::cin >> n >> sum) {
        std::vector<int> arr(n);
        for (auto& it : arr) {
            std::cin >> it;
        }
        std::vector<int> max(1+n, -INF);
        for (int i = n-1; i >= 0; --i) {
            max[i] = std::max(max[i+1], arr[i]);
        }
        int res = sum;
        for (int i = 0; i+1 < n; ++i) {
            int nDollars = sum / arr[i];
            int temp = (sum % arr[i]) + max[i+1] * nDollars;
            res = std::max(res, temp);
        }
        std::cout << res << std::endl;
    }
    return 0;
}