/*
    Problem: 314A. Sereja and Contest
    
    Solution: math, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Int;
typedef std::vector<int> vi;

vi solve(const int n, const int bound, const vi& arr) {
    Int prefSum = 0; vi ans; int nErased = 0;
    for (int i = 1; i <= n; ++i) {
        Int currDiff = prefSum - (i - 1 - nErased) * Int(n - i) * arr[i];
        if (currDiff < bound) {
            ans.push_back(i);
            nErased++;
        } else {
            prefSum += Int(i - 1 - nErased) * arr[i];
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, bound;
    while (std::cin >> n >> bound) {
        vi arr(1+n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> arr[i];
        }
        vi ans = solve(n, bound, arr);
        for (int id : ans) {
            std::cout << id << "\n";
        }
        std::cout << std::endl;
    }
    return 0;
}