/*
    Problem: 27C. Unordered Subsequence
    
    Solution: dynamic programming, greedy, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Triple {
    int x, y, z;
};

Triple solve(const int n, const std::vector<int>& arr) {
    std::vector<int> rMax(n,n-1), rMin(n,n-1);
    for (int i = n-2; i >= 0; --i) {
        rMax[i] = (arr[i+1] >= arr[rMax[i+1]]) ? (i+1) : rMax[i+1];
        rMin[i] = (arr[i+1] <= arr[rMin[i+1]]) ? (i+1) : rMin[i+1];
    }
    int lMin = 0, lMax = 0;
    for (int i = 1; i+1 < n; ++i) {
        lMin = (arr[i-1] <= arr[lMin]) ? (i-1) : lMin;
        lMax = (arr[i-1] >= arr[lMax]) ? (i-1) : lMax;
        if (arr[lMin] < arr[i] && arr[i] > arr[rMin[i]]) {
            return Triple{lMin+1,i+1,rMin[i]+1};
        }
        if (arr[lMax] > arr[i] && arr[i] < arr[rMax[i]]) {
            return Triple{lMax+1,i+1,rMax[i]+1};
        }
    }
    return Triple{0,0,0};
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> arr(n);
        for (auto &it : arr) {
            std::cin >> it;
        }
        Triple answ = solve(n, arr);
        if (answ.x == 0) {
            std::cout << 0 << std::endl;
        } else {
            std::cout << 3 << std::endl;
            std::cout << answ.x << ' ' << answ.y << ' ' << answ.z << std::endl;
        }
    }
    return 0;
}