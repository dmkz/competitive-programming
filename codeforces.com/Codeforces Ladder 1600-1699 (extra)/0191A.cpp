/*
    Problem: 191A. Dynasty Puzzles
    
    Solution: dynamic programming, strings, O(26*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int INF = (int)1e9;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vvi maxLen(26, vi(26, -INF));
        vi next(26, 0);
        while (n--) {
            std::string s; std::cin >> s;
            int fi = int(s.front()-'a');
            int se = int(s.back()-'a');
            std::fill(next.begin(), next.end(), 0);
            for (int i = 0; i < 26; ++i) {
                next[i] = maxLen[i][fi] + (int)s.size();
            }
            for (int i = 0; i < 26; ++i) {
                maxLen[i][se] = std::max(maxLen[i][se], next[i]);
            }
            maxLen[fi][se] = std::max(maxLen[fi][se], (int)s.size());
        }
        int answ = 0;
        for (int i = 0; i < 26; ++i) {
            answ = std::max(maxLen[i][i], answ);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}