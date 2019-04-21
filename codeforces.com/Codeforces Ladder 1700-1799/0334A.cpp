/*
    Problem: 334A. Candy Bags
    
    Solution: constructive, math, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    vvi arr(n,vi(n));
    for (int i = 0, num = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = num++;
        }
    }
    vvi ans(n);
    for (int j = 0; j < n; ++j) {
        int r = n-1, c = j;
        for (int k = 0; k < n; ++k) {
            ans[j].push_back(arr[r][c]);
            r--;
            c++; if (c >= n) { c = 0; }
        }
    }
    for (int i = 1; i < n; ++i) {
        auto sum1 = std::accumulate(all(ans[0]), 0);
        auto sum2 = std::accumulate(all(ans[i]), 0);
        assert(sum1 == sum2);
    }
    for (auto & row : ans) {
        for (auto it : row) { std::cout << it << ' '; }
        std::cout << '\n';
    }
    return 0;
}