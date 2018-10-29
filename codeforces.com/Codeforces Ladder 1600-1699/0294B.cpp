/*
    Problem: 294B. Shaass and Bookshelf
    
    Solution: dynamic programming, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Pair { int t, w; };

const int INF = (int)1e9;

int solve(const int n, const std::vector<Pair>& arr) {
    std::vector<std::vector<int>> minWidth(1+n, std::vector<int>(2*n+1, INF));
    minWidth[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        int w = arr[i-1].w, t = arr[i-1].t;
        for (int curr = 0; curr <= 2 * n; ++curr) {
            minWidth[i][curr] = std::min(minWidth[i][curr], minWidth[i-1][curr]+w);
            if (curr - t >= 0) {
                minWidth[i][curr] = std::min(minWidth[i][curr], minWidth[i-1][curr-t]);
            }
        }
    }
    int answ = INF;
    for (int curr = 0; curr <= 2 * n; ++curr) {
        if (curr < minWidth[n][curr]) continue;
        answ = std::min(answ, std::max(curr, minWidth[n][curr]));
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<Pair> arr(n);
        for (auto& it : arr) { std::cin >> it.t >> it.w; }
        std::cout << solve(n, arr) << std::endl;
    }
    return 0;
}