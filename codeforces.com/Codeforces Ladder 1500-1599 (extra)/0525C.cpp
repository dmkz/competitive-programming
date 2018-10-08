/*
    Problem: 525C. Ilya and Sticks
    
    Solution: greedy, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for (auto& it : arr) std::cin >> it;
    std::sort(arr.begin(), arr.end());
    std::vector<int> sides;
    while (n > 0) {
        if (n == 1 || arr[n-1] - arr[n-2] > 1) {
            n--;
        } else {
            sides.push_back(arr[n-2]);
            n -= 2;
        }
    }
    int64_t answ = 0;
    for (int i = 0; i+1 < (int)sides.size(); i += 2) {
        answ += 1LL * sides[i] * sides[i+1];
    }
    std::cout << answ;
    return 0;
}