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
// предподсчёт минимальных простых делителей:
const int NMAX = 1024 * 10000;
int minDiv[NMAX+1];
void precalc() {
    // сначала запускаем решето, чтобы отметить все составные числа:
    for (int i = 2; i * i <= NMAX; i++)
        if (!minDiv[i])
            for (int j = i * i; j <= NMAX; j += i)
                if (!minDiv[j])
                    minDiv[j] = i;
    // теперь отметим все простые числа - они делятся сами на себя:
    for (int i = 2; i <= NMAX; i++)
        if (!minDiv[i]) minDiv[i] = i;
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
            // умножение на новое число: обновляем все простые, которые в него входят
            int x; cin >> x;
            st.push(x); // закидываем число x в стек
            while (x > 1) {
                // извлекаем минимальный простой делитель и сокращаем на него:
                int p = minDiv[x];
                x /= p;
                // обновляем степень этого делителя:
                int prev = cnt[p]++;
                answ = divmod(answ, prev+1); // делим на то, что было
                answ = mulmod(answ, prev+2); // умножаем на то, что стало
            }
        } else {
            // отмена операции: делаем то же самое, но в обратном порядке
            int x = st.top();
            st.pop();
            while (x > 1) {
                // извлекаем минимальный простой делитель и сокращаем на него:
                int p = minDiv[x];
                x /= p;
                // обновляем степень этого делителя:
                int prev = cnt[p]--;
                answ = divmod(answ, prev+1); // делим на то, что было
                answ = mulmod(answ, prev);   // умножаем на то, что стало
            }
        }
        // выводим ответ:
        cout << answ << ' ';
    }
    cout << '\n';
}
main() {
    precalc(); // предподсчитываем минимальные простые делители один раз
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
