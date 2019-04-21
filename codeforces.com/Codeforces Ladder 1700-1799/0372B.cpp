/*
    Problem: 372B. Counting Rectangles is Fun
    
    Solution: dynamic programming, O(n^2 * m^3 + q)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
const int NMAX = 41;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    static int cnt[NMAX][NMAX][NMAX][NMAX];
    static int zdn[NMAX][NMAX], arr[NMAX][NMAX], zrt[NMAX][NMAX];
    for (int nR, nC, nQ; std::cin >> nR >> nC >> nQ; std::cout << std::endl) {
        std::fill(&cnt[0][0][0][0],&cnt[0][0][0][0]+NMAX*NMAX*NMAX*NMAX,0);
        std::fill(&zdn[0][0],&zdn[0][0]+NMAX*NMAX,0);
        std::fill(&zrt[0][0],&zrt[0][0]+NMAX*NMAX,0);
        for (int r = 0; r < nR; ++r) {
            std::string s; std::cin >> s;
            for (int c = 0; c < nC; ++c) {
                arr[r][c] = (s[c] == '1');
            }
        }
        for (int r = nR-1; r >= 0; --r) {
            for (int c = 0; c < nC; ++c) {
                if (arr[r][c]) { continue; }
                zdn[r][c] = 1 + zdn[r+1][c];
            }
        }
        for (int r = 0; r < nR; ++r) {
            for (int c = nC-1; c >= 0; --c) {
                if (arr[r][c]) { continue; }
                zrt[r][c] = 1 + zrt[r][c+1];
            }
        }
        for (int rlen = 1; rlen <= nR; ++rlen) {
            for (int clen = 1; clen <= nC; ++clen) {
                for (int r = 0; r + rlen <= nR; ++r) {
                    for (int c = 0; c + clen <= nC; ++c) {
                        if (rlen == 1 && clen == 1) {
                            cnt[rlen][clen][r][c] = !arr[r][c];
                        } else if (rlen == 1) {
                            int add = std::min(clen,zrt[r][c]);
                            cnt[rlen][clen][r][c] = cnt[rlen][clen-1][r][c+1] + add;
                        } else if (clen == 1) {
                            int add = std::min(rlen,zdn[r][c]);
                            cnt[rlen][clen][r][c] = cnt[rlen-1][clen][r+1][c] + add;
                        } else {
                            cnt[rlen][clen][r][c] += cnt[rlen][clen-1][r][c+1];
                            cnt[rlen][clen][r][c] -= cnt[rlen-1][clen-1][r+1][c+1];
                            cnt[rlen][clen][r][c] += cnt[rlen-1][clen][r+1][c];
                            int min = rlen;
                            int add = 0;
                            for (int w = 1; min > 0 && w <= clen; ++w) {
                                min = std::min(min, zdn[r][c+w-1]);
                                add += min;
                            }
                            cnt[rlen][clen][r][c] += add;
                        }
                    }
                }
            }
        }
        while (nQ--) {
            int r1, c1, r2, c2;
            std::cin >> r1 >> c1 >> r2 >> c2;
            r1--,c1--,r2--,c2--;
            if (r1 > r2) { std::swap(r1, r2); }
            if (c1 > c2) { std::swap(c1, c2); }
            std::cout << cnt[r2-r1+1][c2-c1+1][r1][c1] << '\n';
        }
    }
    return 0;
}