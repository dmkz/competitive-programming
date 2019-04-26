/*
    Problem: 378B. Maximum Submatrix 2
    
    Solution: dynamic programming, events, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int nR, nC;
    while (std::cin >> nR >> nC) {
        std::vector<std::string> arr(nR);
        std::vector<std::vector<uint16_t>> cnt(nR, std::vector<uint16_t>(nC+1));
        for (auto &it : arr) { std::cin >> it; }
        for (int r = 0; r < nR; ++r) {
            for (int c = nC-1; c >= 0; --c) {
                cnt[r][c] = arr[r][c] == '1' ? 1 + cnt[r][c+1] : 0;
            }
        }
        std::vector<bool> opened(nR);
        int answ = 0;
        std::vector<std::vector<uint16_t>> needToClose(nC+1);
        for (int i = 0; i < nC; ++i) {
            int nOpened = 0;
            for (int r = 0; r < nR; ++r) {
                opened[r] = 1;
                nOpened++;
                needToClose[i+cnt[r][i]].push_back(r);
            }
            for (int j = i; nOpened && j < nC; ++j) {
                for (int id : needToClose[j]) {
                    nOpened--;
                    opened[id] = 0;
                }
                answ = std::max(answ, (j-i+1) * nOpened);
            }
            for (auto &it : needToClose) { it.clear(); }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}