// динамическое программирование, возведение матрицы в степень
// Задача: F, Вердикт: OK, Время: 4ms, Память: 2.15Mb
#include <bits/stdc++.h>
#include <cassert>
#define isz(x) (int)(x).size()
const int mod = 998244353;
using ll = long long;
using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;
int dot(const Vector &a, const Vector &b) {
    assert(isz(a) == isz(b));
    int res = 0;
    for (int i = 0; i < isz(a); i++)
        res = int((res + a[i] * 1LL * b[i]) % mod);
    return res;
}
Matrix multiply(const Matrix &a, const Matrix &b) {
    const int n = isz(a);
    const int t = isz(a[0]);
    assert(t == isz(b));
    const int m = isz(b[0]);
    Matrix c(n, Vector(m));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < t; k++)
            for (int j = 0; j < m; j++)
                c[i][j] = (c[i][j] + a[i][k] * 1LL * b[k][j]) % mod;
    return c;
}
Vector multiply(const Matrix &m, const Vector &vec) {
    Vector res(m.size());
    for (int i = 0; i < isz(m); i++)
        res[i] = dot(m[i], vec);
    return res;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // M - 1000, D - 500, C - 100, L - 50, X - 10, V - 5, I - 1
    // нельзя использовать 5 букв, и нельзя ставить рядом VI, IV, II
    Matrix mt(21, Vector(21, 1));
    mt[0][0] = 0;
    mt[0][1] = 0;
    mt[1][0] = 0;
    Vector curr(21, 1);
    ll n; std::cin >> n;
    n--;
    while (n > 0) {
        if (n % 2 == 1) {
            curr = multiply(mt, curr);
        }
        mt = multiply(mt, mt);
        n >>= 1;
    }
    std::cout << dot(curr, Vector(21, 1)) << std::endl;
}
