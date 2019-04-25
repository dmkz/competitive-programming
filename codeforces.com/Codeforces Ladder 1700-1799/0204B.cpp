/*
    Problem: 204B. Little Elephant and Cards
    
    Solution: std::map, counting, sorting, greedy, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vi f(n), b(n);
        std::map<int,int> cnt;
        for (int i = 0; i < n; ++i) {
            std::cin >> f[i] >> b[i];
            cnt[f[i]]++;
            cnt[b[i]]++;
        }
        const int need = (n + 1) / 2;
        int answ = INT_MAX;
        for (const auto & pt : cnt) {
            const int color = pt.first;
            const int count = pt.second;
            if (count < need) {
                continue;
            }
            int have = 0;
            for (auto it : f) {
                have += (it == color);
            }
            int temp = 0;
            for (int i = 0; have < need && i < n; ++i) {
                if (f[i] != color && b[i] == color) {
                    have++;
                    temp++;
                }
            }
            if (have >= need) {
                answ = std::min(answ, temp);
            }
        }
        if (answ == INT_MAX) { answ = -1; }
        std::cout << answ << std::endl;
    }
    return 0;
}