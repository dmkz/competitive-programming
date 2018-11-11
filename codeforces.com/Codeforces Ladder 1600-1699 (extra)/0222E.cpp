/*
    Problem: 222E. Decoding Genome
    
    Solution: combinatorics, math, matrix multiplication, O(log(n) * k^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int get_id(char c) {
    return ('a' <= c && c <= 'z') ? int(c - 'a') : int(c - 'A') + 26;
}

const int mod = (int)1e9+7;

int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

int sub(int a, int b) {
    return (a -= b) < 0 ? a + mod : a;
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

struct Matrix {

    vvi data;
    
    Matrix(const vvi& matr) : data(matr) { }

    Matrix operator*(const Matrix &m) const {
        const int n = (int)data.size();
        vvi ret(n, vi(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    ret[i][j] = add(ret[i][j], mul(data[i][k], m.data[k][j]));
                }
            }
        }
        return Matrix(ret);
    }
    
};

Matrix mpow(Matrix a, int64_t n) {
    Matrix res(a);
    n--;
    while (n > 0) {
        if (n & 1) {
            res = res * a;
        }
        n >>= 1;
        a = a * a;
    }
    return res;
}

int main() {
    int nLetters, nRules; int64_t n;
    while (std::cin >> n >> nLetters >> nRules) {
        vvi next(nLetters, vi(nLetters, 1));
        while (nRules--) {
            std::string s; std::cin >> s;
            int u = get_id(s[0]), v = get_id(s[1]);
            next[u][v] = 0;
        }
        if (n == 1) {
            std::cout << nLetters << std::endl;
        } else {
            Matrix matr(next);
            matr = mpow(matr, n-1);
            int res = 0;
            for (int i = 0; i < nLetters; ++i) {
                for (int j = 0; j < nLetters; ++j) {
                    res = add(res, matr.data[i][j]);
                }
            }
            std::cout << res << std::endl;
        }
    }
    return 0;
}