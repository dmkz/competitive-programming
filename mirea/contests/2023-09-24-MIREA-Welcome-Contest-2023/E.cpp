#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int getDigit(char c) {
    switch(c) {
        case '0' ... '9': return c - '0';
        case 'A' ... 'Z': return c - 'A' + 10;
        case 'a' ... 'z': return c - 'a' + 36;
    }
    assert(false);
    return -1;
}
const int mod = (int)1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        // Надо посчитать (L+R)*(R-L+1)/2 по модулю mod
        // Деление заменяем умножением по модулю
        // Взятие модуля вносим внутрь скобок
        // Получится (L % mod + R % mod) * (R % mod - L % mod + 1) * (mod + 1) / 2
        // получается, что надо вычислить L % mod и R % mod
        // вычисляем слева-направо, используя представление чисел в системе
        // счисления по основанию b. Надо посчитать
        // a0 + a1 * b + a2 * b^2 + ... % mod в цикле for
        int n, b; cin >> n >> b;
        ll L = 0, R = 0;
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            L = (L * b + getDigit(c)) % mod;
        }
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            R = (R * b + getDigit(c)) % mod;
        }
        // (L+R)*(R-L+1)/2
        ll res = (L + R) * (R - L + 1 + mod) % mod;
        res *= (mod+1)/2;
        res %= mod;
        cout << res << endl;
    }
}