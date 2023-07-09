#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main() {
    // ответ: t-й член геометрической прогрессии a(t) = x * q^t
    // по тестам из условия найдём x и q
    // также используем тот факт, что ответ - целое число (тоже из условия задачи)
    ld q = cbrtl(352947/1029); // q = кубический корень(a(6)/a(3))
    ld x = 1029/powl(q,3); // x = a(3) / q^3
    // отвечаем на запросы:
    int tt; cin >> tt;
    while (tt --> 0) {
        int t; cin >> t;
        cout << (int64_t)(x * powl(q, t)) << '\n';
    }
    return 0;
}
