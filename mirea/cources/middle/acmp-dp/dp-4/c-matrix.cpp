#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
const int mod = (int)1e9+9;
vvi mult(vvi A, vvi B) {
    vector C(isz(A),vector(isz(B[0]), 0ULL));
    for (int i = 0; i < isz(A); i++) {
        for (int k = 0; k < isz(A[0]); k++) {
            for (int j = 0; j < isz(B[0]); j++) {
                C[i][j] += A[i][k] * 1LL * B[k][j];
                if (C[i][j] >= (ull)16e18L) {
                    C[i][j] %= mod;
                }
            }
        }
    }
    vvi res(isz(A),vi(isz(B[0])));
    for (int i = 0; i < isz(res); i++)
        for (int j = 0; j < isz(res[0]); j++)
            res[i][j] = int(C[i][j] % mod);
    return res;
}
vi mult(vvi A, vi b) {
    vvi B(isz(b),{0});
    for (int i = 0; i < isz(b); i++)
        B[i][0] = b[i];
    B = mult(A,B);
    for (int i = 0; i < isz(b); i++)
        b[i] = B[i][0];
    return b;
}
vvi matPow(vvi A, ll n) {
    vvi res(isz(A),vi(isz(A)));
    for (int i = 0; i < isz(res); i++)
        res[i][i] = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            res = mult(res, A);
        }
        A = mult(A,A);
        n >>= 1;
    }
    return res;
}
bool isPrime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return x > 1;
}
int main() {
    vvi A(100, vi(100,0));
    vi b(100);
    for (int x = 100; x <= 999; x++) {
        if (isPrime(x)) {
            A[x%100][x/10]=1;
            b[x%100]++;
        }
    }    
    int t = 1; //cin >> t;
    while (t --> 0) {
        ll n; cin >> n;
        auto answ = mult(matPow(A,n-3),b);
        int res = 0;
        for (auto it : answ) {
            res += it;
            res %= mod;
        }
        cout << res << '\n';
    }
}