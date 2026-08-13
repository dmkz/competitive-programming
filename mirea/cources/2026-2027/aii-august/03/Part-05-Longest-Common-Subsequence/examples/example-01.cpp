#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем две строки:
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    // dp[i][j] — длина LCS первых i символов s и первых j символов t.
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    vector<vector<pair<int, int>>> parent(n + 1, vector<pair<int, int>>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i - 1] == t[j - 1]) {
                // Совпавшие последние символы добавляют один к ответу для более коротких префиксов.
                dp[i][j] = dp[i - 1][j - 1] + 1;
                parent[i][j] = {i - 1, j - 1};
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                // Отбрасываем последний символ строки s и при равенстве выбираем верхнего соседа.
                dp[i][j] = dp[i - 1][j];
                parent[i][j] = {i - 1, j};
            } else {
                // Отбрасываем последний символ строки t.
                dp[i][j] = dp[i][j - 1];
                parent[i][j] = {i, j - 1};
            }
        }
    }
    // Восстанавливаем ответ по parent и добавляем символы диагональных переходов.
    string answ;
    for (int i = n, j = m; i > 0 && j > 0;) {
        auto [prevI, prevJ] = parent[i][j];
        // Диагональный переход означает, что символ s[i - 1] вошёл в подпоследовательность.
        if (prevI == i - 1 && prevJ == j - 1) answ.push_back(s[i - 1]);
        // Переходим в сохранённое состояние-предок.
        i = prevI;
        j = prevJ;
    }
    // Символы добавлены с конца подпоследовательности, поэтому разворачиваем их.
    reverse(answ.begin(), answ.end());
    cout << answ.size() << '\n' << answ << '\n';
}