/*
    Problem: 362B. Petya and Staircases
    
    Solution: sorting, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> arr(m);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    bool flag = !std::binary_search(arr.begin(), arr.end(), 1);
    flag = flag && !std::binary_search(arr.begin(), arr.end(), n);
    for (int i = 1; i+1 < m; ++i) {
        if (arr[i-1]+1 == arr[i] && arr[i]+1 == arr[i+1]) {
            flag = false;
            break;
        }
    }
    std::cout << (flag ? "YES" : "NO");
    return 0;
}