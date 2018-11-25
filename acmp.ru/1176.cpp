/*
    Задача: 1176. Минимумы в прямоугольнике
    
    Решение: Двумерная Sparse Table, O(n*m*log(n)*log(m)+k)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#pragma GCC optimize ("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,sse4a")
//#prama GCC target("avx,avx2")

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <random>

namespace SparseTable {

    const int NMAX = 300, PMAX = 8, INF = (int)1e9+7;

    int data[1+PMAX][1+PMAX][1+NMAX][1+NMAX], log2[1+NMAX];
    
    void init() {
        log2[0] = log2[1] = 0;
        for (int i = 2; i <= NMAX; ++i) {
            log2[i] = log2[i / 2] + 1;
        }
        std::fill(&data[0][0][0][0],&data[0][0][0][0]+(1+PMAX)*(1+PMAX)*(1+NMAX)*(1+NMAX),INF);
    }
    
    void set(int r, int c, int x) {
        data[0][0][r][c] = x;
    }
    
    void build() {
        for (int pc = 1; pc <= PMAX; ++pc) {
            for (int r = 1; r <= NMAX; ++r) {
                for (int c = 1; c + (1 << pc) - 1 <= NMAX; ++c) {
                    int v1 = data[0][pc-1][r][c];
                    int v2 = data[0][pc-1][r][c+(1 << (pc - 1))];
                    data[0][pc][r][c] = std::min(v1, v2);
                }
            }
        }
        for (int pr = 1; pr <= PMAX; ++pr) {
            for (int pc = 0; pc <= PMAX; ++pc) {
                for (int r = 1; r + (1 << pr) - 1 <= NMAX; ++r) {
                    for (int c = 1; c + (1 << pc) - 1 <= NMAX; ++c) {
                        int v1 = data[pr-1][pc][r][c];
                        int v2 = data[pr-1][pc][r+(1<<(pr-1))][c];
                        data[pr][pc][r][c] = std::min(v1, v2);
                    }
                }
            }
        }
    }
    
    int get(int r1, int c1, int r2, int c2) {
        if (r1 > r2) std::swap(r1, r2);
        if (c1 > c2) std::swap(c1, c2);
        int pr = log2[r2-r1+1];
        int pc = log2[c2-c1+1];
        r2 = r2 - (1 << pr) + 1;
        c2 = c2 - (1 << pc) + 1;
        return std::min({
            data[pr][pc][r1][c1], data[pr][pc][r1][c2],
            data[pr][pc][r2][c1], data[pr][pc][r2][c2]
        });
    }
}

int main() {
    int nRows, nCols, nQueries;
    scanf("%d %d %d", &nRows, &nCols, &nQueries);
    SparseTable::init();
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            int v; scanf("%d", &v);
            SparseTable::set(r,c,v);
        }
    }
    SparseTable::build();
    while (nQueries--) {
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        printf("%d\n", SparseTable::get(r1,c1,r2,c2));
    }
    return 0;
}