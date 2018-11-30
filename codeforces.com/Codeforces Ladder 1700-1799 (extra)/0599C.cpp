/*
    Problem: 599C. Day at the Beach
    
    Solution: greedy, sorting, binary search, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

#define all(x) (x).begin(), (x).end()

typedef std::vector<int> vi;

int solve(const int n, vi arr) {
    vi items = arr, cnt(n);
    std::sort(all(items));
    for (auto &it : arr) {
        int tmp = it = int(std::lower_bound(all(items), it) - items.begin());
        it += cnt[it];
        cnt[tmp]++;
    }
    int max = -1, answ = 0;
    for (int i = 0; i < n; ++i) {
        max = std::max(max, arr[i]);
        answ += (max == i);
    }
    return answ;
}

int main() {
    int n;
    while (std::cin >> n) {
        vi arr(n);
        for (auto &it : arr) {
            std::cin >> it;
        }
        std::cout << solve(n, arr) << std::endl;
    }
    return 0;
}