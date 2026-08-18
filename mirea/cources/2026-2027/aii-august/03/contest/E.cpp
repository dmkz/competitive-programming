#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
int dp[1001][1001]; // глобальный массив нужен из-за мультитестов
                    // нельзя выделять массив 1001 * 1001 для каждого теста, так как их 10000
void solve() {
    // читаем данные:
    string s, t;
    cin >> s >> t;
    s = "$" + s;
    t = "^" + t;
    // инициализируем динамику:
    for (int i = 1; i < isz(s); i++)
        for (int j = 1; j < isz(t); j++)
            if (s[i] == t[j]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    // отдельно вынесем функцию вычисления i-й строки: она получается удалением цикла по j
    auto calcIthRow = [&](int i) {
        for (int j = 1; j < isz(t); j++)
            if (s[i] == t[j]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    };
    // отдельно вынесем функцию вычисления j-го столбца: она получается удалением цикла по i
    auto calcJthCol = [&](int j) {
        for (int i = 1; i < isz(s); i++)
            if (s[i] == t[j]) dp[i][j] = 1 + dp[i-1][j-1];
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    };
    // обрабатываем запросы:
    int q; cin >> q;
    while (q --> 0) {
        string query; cin >> query;
        if (query == "S+") {
            // читаем символ, добавляем его в конец строки "s", и вычисляем новую строку ДП:
            char ch; cin >> ch;
            s.push_back(ch);
            calcIthRow(isz(s)-1);
        } else if (query == "T+") {
            // читаем символ, добавляем его в конец строки "t", и вычисляем новый столбец ДП:
            char ch; cin >> ch;
            t.push_back(ch);
            calcJthCol(isz(t)-1);
        } else if (query == "S-") {
            // просто удаляем последний символ строки s
            s.pop_back();
        } else if (query == "T-") {
            // просто удаляем последний символ строки t
            t.pop_back();
        }
        // выводим ответ:
        cout << dp[isz(s)-1][isz(t)-1] << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
