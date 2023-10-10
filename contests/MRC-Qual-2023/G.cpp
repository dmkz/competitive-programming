#include <bits/stdc++.h>
using namespace std;
int main() {
    int k; cin >> k;
    uint64_t x; cin >> x;
    // найдём мантиссу, порядок и знак
    uint64_t m = x & ((1ULL << k) - 1); // мантисса
    uint64_t p = (x << 1 >> 1) >> k; // порядок
    uint64_t s = x >> 63; // знак
    // проверим, что не NaN (порядок состоит из одних 1)
    bool isNaN = true;
    for (int i = k; i < 63; i++)
        isNaN &= (((x >> i) & 1) == 1);
    if (isNaN) {
        cout << "NaN" << endl;
        return 0;
    }
    // проверим что не ноль:
    if (m == 0) {
        cout << "0" << endl;
        return 0;
    }
    // далее общий случай:
    int64_t power;
    if (p > 0) {
        power = p + 1 - (1LL << (62 - k));
        // случай вида 2^power * (1 + m / 2^k)
        // мы будем вносить одну двойку в скобку пока m не поделится на 2^k
        // нам понадобится внести k двоек
        // 2^power * ((2^k + m) / 2^k)
        m += (1ULL << k);
        power -= k;
    } else if (p == 0) {
        // случай вида m * 2^power
        power = -k + (1 - (1LL << (62 - k)));
    }
    // доводим m до нечётного числа
    while (m % 2 == 0) {
        m /= 2;
        power++;
    }
    // выводим ответ
    if (s) cout << "-";
    cout << m;
    if (power != 0) {
        if (power < 0) cout << "/2**" << -power;
        else cout << "*2**" << power;
    }
    cout << endl;
    return 0;
}
