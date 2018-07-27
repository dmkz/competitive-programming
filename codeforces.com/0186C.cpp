/*
    Problem: 186C. Plant
    
    Solution: recurrent sequence, operator, matrices, vectors, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

const ll mod = ll(1e9)+7;

struct Vector {
    ll a, b;
};

struct Matrix {
    ll a, b, c, d;
    
    Matrix mul(const Matrix& m) const {
        return Matrix{
            (a * m.a + b * m.c) % mod, (a * m.b + b * m.d) % mod,
            (c * m.a + d * m.c) % mod, (c * m.b + d * m.d) % mod
        };
    }
    
    Vector mul(const Vector& v) const {
        return Vector{
            (a * v.a + b * v.b) % mod, 
            (c * v.a + d * v.b) % mod
        };
    }
};

Matrix pow(Matrix a, ll n) {
    Matrix res{1,0,0,1};
    while (n > 0) {
        if (n % 2 == 1) {
            res = res.mul(a);
        }
        a = a.mul(a);
        n /= 2;
    }
    return res;
}

int main() {
    Matrix A{3,1,1,3};
    Vector x{1,0};
    ll n;
    std::cin >> n;
    x = pow(A, n).mul(x);
    std::cout << x.a;
    return 0;
}