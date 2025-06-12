#include <bits/stdc++.h>
using namespace std;
int64_t minPrimeDivisor(int64_t x) {
    for (int64_t i = 2; i * i <= x; i++)
        if (x % i == 0)
            return i;
    return x;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int64_t x, n; cin >> x >> n;
        // сначала делаем первое прибавление
        assert(n > 0);
        x += minPrimeDivisor(x);
        n--;
        // после него число x всегда чётное и начинает делиться на 2
        assert(x % 2 == 0);
        x += n * 2;
        // выводим ответ
        cout << x << "\n";
    }
}
