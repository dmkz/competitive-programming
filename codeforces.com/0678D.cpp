// математика, линейная функция, геометрическая прогрессия
#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9+7;
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
int add(int a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}
int sub(int a, int b) {
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}
int binpow(int a, int64_t n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = mul(r, a);
        a = mul(a, a);
        n /= 2;
    }
    return r;
}
int inv(int a) {
    return binpow(a, mod-2);
}
main() {    
    int A, B, x;
    int64_t n;
    cin >> A >> B >> n >> x;
    // Выведем формулу. 
    // Вычислим f(f(x)) = A*(A*x+B)+B=A^2*x+A*B+B
    // Вычислим f(f(f(x))) = A*(A^2*x+A*B+B)+B = A^3 * x + A^2 * B + A * B + B.
    // Выведем закономерность. После n вычислений, формула примет вид:
    // f_n(x) = A^n * x + B * (1 + A + ... + A^{n-1})
    // Или: A^n * x + B * (A^n - 1) / (A - 1)
    // Аккуратно вычисляем знамение по простому модулю 10^9+7:
    if (A == 1) { // крайний случай
        cout << add(x, mul(B, int(n % mod))) << endl;
        return 0;
    }
    const int An = binpow(A, n);
    const int res = add(mul(An, x), mul(B, mul(sub(An, 1), inv(sub(A, 1)))));
    cout << res << endl;
}
