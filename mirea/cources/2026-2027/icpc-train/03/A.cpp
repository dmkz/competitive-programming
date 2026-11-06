#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
const int inf = (int)1e9+7;
void flip(string &s, int i, int j) {
    s[i] = char('T' - s[i] + 'H');
    s[j] = char('T' - s[j] + 'H');
}
int solve(string s, int fi, int se) {
    const int n = (int)s.size();
    flip(s, fi, se);
    int answ = 1;
    for (int i = se; i != fi; (i += 1) %= n)
        if (s[i] == 'T')
            flip(s, i, (i+1)%n), answ++;
    return (s == string(n, 'H') ? answ : inf);
}
void solve() {
    // читаем входные данные
    string s; cin >> s;
    const int n = (int)s.size();
    // находим символ i, который мы должны будем поменять. Либо мы меняем пару (i-1, i).
    // Либо меняем пару (i, i+1). Рассматриваем оба варианта, считаем ответ для каждого, и выводим минимум
    int answ = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == 'T') {
            int fi = solve(s, i, (i+1) % n);
            int se = solve(s, (i-1+n) % n, i);
            answ = min(fi, se);
            break;
        }
    if (answ >= inf) answ = -1;
    cout << answ << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}