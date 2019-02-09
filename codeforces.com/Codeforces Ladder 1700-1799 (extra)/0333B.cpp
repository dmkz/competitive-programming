/*
    Problem: 333B. Chips
    
    Solution: greedy, constructive, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, nBanned;
    while (std::cin >> n >> nBanned) {
        std::vector<bool> bannedCol(1+n), bannedRow(1+n);
        for (int i = 0, r, c; i < nBanned; ++i) {
            std::cin >> r >> c;
            bannedRow[r] = bannedCol[c] = true;
        }
        int answ = 0;
        if (n % 2 == 1) { answ += !bannedCol[(n+1)/2] || !bannedRow[(n+1)/2]; }
        for (int r1 = 2; r1 <= n / 2; ++r1) {
            int r2 = n - r1 + 1;
            int c1 = r2, c2 = r1;
            answ += !bannedRow[r1] + !bannedCol[c1] + !bannedRow[r2] + !bannedCol[c2];
        }
        std::cout << answ << std::endl;
    }
    return 0;
}