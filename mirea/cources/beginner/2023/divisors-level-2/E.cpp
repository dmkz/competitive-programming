#include <bits/stdc++.h>
using namespace std;
int main() {
    int64_t n, k;
    cin >> n >> k;
    // a1+a2+a3+...+ak = n, n делится на НОД, значит каждое слагаемое делится на НОД
    // НОД * (b1 + b2 + b3 + ... + bk) = n
    // переберём НОД, дальше попробуем заполнить скобку минимальными различными числами:
    // (1 + 2 + 3 + ... + (k-1) + остаток) = n / НОД
    int64_t answ = -1;
    for (int64_t x = 1; x * x <= n; x++)
        if (auto y = n / x; y * x == n) {
            auto update_answer = [&](int64_t nod)
            {
                int64_t sum = n / nod;
                // если можем выбрать последнее число, которое > k-1:
                if (sum - __int128(k-1) * k / 2 >= k)
                    answ = max(answ, nod);
            };
            update_answer(x);
            update_answer(y);
        }
    // выводим ответ:
    if (answ == -1) cout << "-1\n";
    else {
        for (int64_t i = 1; i <= k-1; i++) {
            cout << answ * i << ' ';
            n -= answ * i;
        }
        cout << n << '\n';
    }
}