#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем строку
    string s; cin >> s;
    // сюда будем записывать результат операций
    vector<string> res = {s};
    // Сравниваем симметричные символы относительно середины и если они не равны
    // то заменяем один на другой
    for (int i = 0, j = (int)s.size()-1; i < j; i++,j--) {
        if (s[i] != s[j]) {
            s[i] = s[j];
            res.push_back(s);
        }
    }
    // выводим ответ
    cout << res.size()-1 << "\n";
    for (auto &s : res)
        cout << s << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
