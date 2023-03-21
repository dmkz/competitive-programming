#include <bits/stdc++.h>
using namespace std;
int main() {
    int nTests;
    cin >> nTests;
    while (nTests--) {
        // читаем n:
        int64_t n;
        cin >> n;
        // находим минимальный простой делитель
        int64_t x = 2, p, q;
        while (x * x * x <= n && n % x != 0) x++;
        // мы нашли либо p, либо q, в любом случае поделим на него
        n /= x;
        if (n % x == 0) // делится на x ещё раз => значит x = p
            p = x, q = n / x;
        else // иначе x = q
            q = x, p = (int)sqrtl(n);
        // выводим ответ:
        cout << p << ' ' << q << '\n';
    }
}