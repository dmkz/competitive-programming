/*
    "Чипполино": двумерное дерево Фенвика, сумма в прямоугольнике, O(q*log(n)^2)
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

typedef long long ll;

struct Fenwick2D {
    
    const int nRows, nCols;
    
    std::vector<std::vector<ll>> data[4];
    
    Fenwick2D(int nRows_, int nCols_)
        : nRows(nRows_+1), nCols(nCols_+1)
    {
        for (int i = 0; i < 4; ++i) {
            data[i].assign(nRows, std::vector<ll>(nCols));
        }
    }
    
    void inc(int row, int col, ll value) {
        const ll d[4] = {value, (1 - col) * value, (1 - row) * value, (1 - row) * (1 - col) * value};
        for (int r = row; r < nRows; r |= r+1) {
            for (int c = col; c < nCols; c |= c+1) {
                data[0][r][c] += d[0];
                data[1][r][c] += d[1];
                data[2][r][c] += d[2];
                data[3][r][c] += d[3];
            }
        }
    }
    
    ll get(int row, int col) const {
        ll d[4] = {};
        for (int r = row; r >= 0; r = (r & (r + 1)) - 1) {
            for (int c = col; c >= 0; c = (c & (c + 1)) - 1) {
                d[0] += data[0][r][c];
                d[1] += data[1][r][c];
                d[2] += data[2][r][c];
                d[3] += data[3][r][c];
            }
        }
        return row * col * d[0] + row * d[1] + col * d[2] + d[3];
    }
    
    void inc(int r1, int c1, int r2, int c2, ll value) {
        inc(  r1,   c1,  value);
        inc(r2+1, c2+1,  value);
        inc(r2+1,   c1, -value);
        inc(  r1, c2+1, -value);
    }
    
    inline ll get(int r1, int c1, int r2, int c2) const {
        return get(r2, c2) - get(r1-1, c2) - get(r2, c1-1) + get(r1-1, c1-1);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nRows, nCols, nQueries;
    std::cin >> nRows >> nCols >> nQueries;
    Fenwick2D fenwick(nRows, nCols);
    
    while (nQueries--) {
        int t, r1, c1, r2, c2;
        std::cin >> t >> r1 >> c1 >> r2 >> c2;
        if (t == 2) {
            int value; std::cin >> value;
            fenwick.inc(r1, c1, r2, c2, value);
        } else {
            auto answ = fenwick.get(r1, c1, r2, c2);
            if (answ > 0) {
                std::cout << "Friends\n";
            } else if (answ < 0) {
                std::cout << "Enemies\n";
            } else {
                std::cout << "I don't know\n";
            }
        }
    }
    
    return 0;
}