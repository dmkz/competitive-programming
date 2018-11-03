/*
    Problem: 402B. Trees in a Row
    
    Solution: brute force, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdlib>

typedef std::vector<int> vi;

vi solve(int n, int k, const vi& arr) {
    vi ret(n); int opt = (int)1e9+1;
    for (int i = 1; i <= 1000; ++i) {
        vi tmp(n, i);
        for (int j = 1; j < n; ++j) { tmp[j] = tmp[j-1] + k; }
        int res = 0;
        for (int j = 0; j < n; ++j) {
            res += (tmp[j] != arr[j]);
        }
        if (res < opt) {
            opt = res;
            ret = tmp;
        }
    }
    return ret;
}

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        vi arr(n);
        for (auto& it : arr) { std::cin >> it; }
        auto opt = solve(n, k, arr);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += (opt[i] != arr[i]);
        }
        std::cout << res << std::endl;
        for (int i = 0; i < n; ++i) {
            if (arr[i] == opt[i]) continue;
            if (arr[i] < opt[i]) {
                std::cout << "+ " << i+1 << " " << opt[i] - arr[i] << "\n";
            } else {
                std::cout << "- " << i+1 << " " << arr[i] - opt[i] << "\n";
            }
        }
    }
    return 0;
}