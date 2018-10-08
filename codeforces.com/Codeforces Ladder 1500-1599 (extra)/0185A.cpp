/*
    Problem: 185A. Plant
    
    Solution: matrix, vector, math, pow, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

const int mod = (int)1e9+7;

struct Vector {
    ll a, b;
};

struct Matrix {
    ll a, b, c, d;
    
    Matrix mult(Matrix& m) {
        return Matrix{
            (a * m.a + b * m.c) % mod, (a * m.b + b * m.d) % mod,
            (c * m.a + d * m.c) % mod, (c * m.b + d * m.d) % mod
        };
    }
    
    Vector mult(Vector& v) {
        return Vector{
            (a * v.a + b * v.b) % mod,
            (c * v.a + d * v.b) % mod
        };
    }
};

Matrix pow(Matrix a, ll n) {
    Matrix res{1,0,0,1};
    while (n > 0) {
        if (n & 1) {
            res = res.mult(a);
        }
        a = a.mult(a);
        n /= 2;
    }
    return res;
}

int main() {
    ll n; std::cin >> n;
    Matrix A{3,1,1,3};
    Vector x{1,0};
    x = pow(A,n).mult(x);
    std::cout << x.a;
    return 0;
}