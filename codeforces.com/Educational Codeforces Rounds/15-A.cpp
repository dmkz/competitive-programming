/*
    Problem: 702A. Maximum Increase
    
    Solution: implementation, O(n)
    
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
    std::vector<ll> arr(n);
    for(auto& it : arr) std::cin >> it;
    arr.push_back(0);
    int answ = 1;
    for (int i = 1, len = 1; i <= n; ++i) {
        if (arr[i] > arr[i-1]) {
            len++;
        } else {
            answ = std::max(answ, len);
            len = 1;
        }
    }
    std::cout << answ;
    
    return 0;
}