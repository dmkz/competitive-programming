#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using vi = std::vector<int>;
const int mod = 998244353;
int sum(int x) {
    return x < 10 ? x : x % 10 + sum(x / 10);
}
void solve() {
    ll n; int m;
    std::cin >> n >> m;
    vi isOK(28); // какая сумма цифр нам подходит
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        isOK[a] = 1;
    }
    vi curr(100), next(100);
    for (int num = 100; num <= 999; num++)
        if (isOK[sum(num)])
            curr[num % 100]++;
    for (ll len = 4; len <= n; len++) {
        std::fill(all(next), 0);
        for (int d = 0; d <= 9; d++) {
            for (int was = 0; was <= 99; was++) {
                if (isOK[sum(was * 10 + d)]) {
                    int &to = next[was % 10 * 10 + d];
                    to += curr[was];
                    if (to >= mod)
                        to -= mod;
                }
            }
        }
        std::swap(curr, next);
    }
    int answ = 0;
    for (auto it : curr) {
        answ += it;
        if (answ >= mod)
            answ -= mod;
    }
    std::cout << answ << std::endl;
}
using Vector = std::vector<int>;
using Matrix = std::vector<Vector>;
int dot(const Vector &a, const Vector &b) {
    assert(isz(a) == isz(b));
    int res = 0;
    for (int i = 0; i < isz(a); i++)
        res = int((res + a[i] * 1LL * b[i]) % mod);
    return res;
}
Vector mult(Matrix A, Vector b) {
    Vector c(A.size());
    for (int r = 0; r < isz(A); r++)
        c[r] = dot(A[r], b);
    return c;
}
Matrix mult(Matrix A, Matrix B) {
    const int n = isz(A);
    assert(isz(A[0]) == n);
    assert(isz(B) == n);
    assert(isz(B[0]) == n);
    Matrix C(n, Vector(n));
    for (int r = 0; r < n; r++)
        for (int k = 0; k < n; k++)
            for (int c = 0; c < n; c++)
                C[r][c] = int((C[r][c] + A[r][k] * 1LL * B[k][c]) % mod);
    return C;
}
void solveFast() {
    ll n; int m;
    std::cin >> n >> m;
    vi isOK(28); // какая сумма цифр нам подходит
    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        isOK[a] = 1;
    }
    vi curr(100), next(100);
    for (int num = 100; num <= 999; num++)
        if (isOK[sum(num)])
            curr[num % 100]++;
    Matrix A(100, Vector(100));
    for (int d = 0; d <= 9; d++) {
        for (int was = 0; was <= 99; was++) {
            if (isOK[sum(was * 10 + d)]) {
                A[was % 10 * 10 + d][was]++;
            }
        }
    }
    n -= 3;
    while (n > 0) {
        if (n % 2 == 1)
            curr = mult(A, curr);
        A = mult(A, A);
        n >>= 1;
    }
    int answ = 0;
    for (auto it : curr) {
        answ += it;
        if (answ >= mod)
            answ -= mod;
    }
    std::cout << answ << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solveFast();
}
