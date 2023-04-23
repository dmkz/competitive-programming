/*
    Задача: произведение последовательности по модулю
*/
#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9+7;
int main() {
    // ускоряем ввод-вывод (обязательно):
    ios::sync_with_stdio(false);
    cin.tie(0);
    // решаем задачу:
    int n; cin >> n;
    int res{1};
    while (n --> 0) {
        int64_t a; cin >> a;
        int rem = (a % mod + mod) % mod;
        res = (res * 1LL * rem % mod);
    }
    cout << res << '\n';
}