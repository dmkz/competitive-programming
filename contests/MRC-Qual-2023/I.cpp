#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
const int mod = 998244353;
int32_t main() {
    // не более одного не делится на три
    // это значит одно или ноль не делится на три
    // это значит либо все делятся на три
    // либо ровно одно не делится на три, а все остальные делятся на три
    // делится на три => сумма цифр делится на три
    // разбить число на отрезки, сумма на которых делится на три
    // если используем префикс-суммы, то (S[R] - S[L-1]) % 3 == 0
    // отсюда S[R] % 3 == S[L-1] % 3
    // выпишем остатки от деления на 3 всех (n+1) префикс-сумм
    // надо выбирать одинаковые остатки на префиксе и одинаковые
    // остатки на суффиксе
    // на префиксе все нули
    // на суффиксе s[N+1]%3
    vector<int> powerOf2(100100, 1);
    for (int i = 1; i < isz(powerOf2); i++)
        powerOf2[i] = powerOf2[i-1] * 2LL % mod;
    string s;
while (cin >> s) {
    vector<int> rems{0};
    for (auto c : s)
        rems.push_back((rems.back() + (c - '0')) % 3);
    if (rems.front() == rems.back()) {
        int zeros{};
        for (auto it : rems)
            zeros += (it == 0);
        cout << powerOf2[zeros-2] << endl;
    } else {
        int equalToFront = 0;
        int equalToBack = 0;
        for (int i = 0; i < isz(rems); i++)
            equalToBack += (rems[i] == rems.back());
        int64_t answ{};
        for (int i = 0; i < isz(rems); i++) {
            equalToBack -= (rems[i] == rems.back());
            if (rems[i] == rems.front()) {
                equalToFront++;
                int left = 1, right = 0;
                if (equalToFront >= 2) {
                    // начало фиксировано, текущий элемент - тоже
                    // остальные равные им можем брать всеми способами
                    left = powerOf2[equalToFront-2];
                }
                if (equalToBack >= 1) {
                    // конец точно берём, а остальные - произвольными способами
                    right = powerOf2[equalToBack-1];
                }
                answ += left * 1LL * right;
                answ %= mod;
            }
        }
        cout << answ << endl;
    }
}
}
