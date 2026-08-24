#include <bits/stdc++.h>
using namespace std;
// операции по простому модулю:
const int mod = 998244353;
// умножение:
int mulmod(int a, int b) { 
    return int(a * 1LL * b % mod);
}
// возведение в степень:
int binpow(int a, int64_t n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = int(r * 1LL * a % mod);
        a = int(a * 1LL * a % mod);
        n >>= 1;
    }
    return r;
}
// обратный:
int invmod(int b) {
    return binpow(b, mod-2);
}
// деление:
int divmod(int a, int b) {
    return mulmod(a, invmod(b));
}
// решение задачи:
void solve() {
    int q; cin >> q;
    stack<int> st; // стек запросов в порядке обработки
    map<int, int> cnt; // количество каждого простого числа
    int answ = 1; // текущее количество делителей
    while (q --> 0) {
        char t; cin >> t;
        if (t == '+') {
            // умножение на новое число: увеличиваем количество и обновляем ответ
            int p; cin >> p;
            st.push(p);
            int prev = cnt[p]++;
            answ = divmod(answ, prev+1); // делим на то, что было
            answ = mulmod(answ, prev+2); // умножаем на то, что стало
        } else {
            // отмена операции: уменьшаем количество и обновляем ответ
            int p = st.top();
            st.pop();
            int prev = cnt[p]--;
            answ = divmod(answ, prev+1); // делим на то, что было
            answ = mulmod(answ, prev);   // умножаем на то, что стало
        }
        // выводим ответ:
        cout << answ << ' ';
    }
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
