// Прочитаем шаблон скобочной строки и запустим рекурсивный перебор вариантов.
// Если позиция равна "?", то мы можем поставить как открывающую скобку, так и закрывающую.
// Если позиция равна "(" или ")", то ставим именно эту скобку.
// Поддерживаем баланс открытых скобок. Запрещено ставить закрывающую скобку, если баланс
// становится отрицательным. В конце перебора выводим те строки, баланс которых равен 0.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные
    int n; cin >> n;
    string pattern; cin >> pattern;
    // запускаем рекурсию
    string s;
    bool was = false;
    function<void(int, int)> dfs = [&](int i, int balance) {
        if (i == n) {
            if (balance == 0) {
                cout << s << '\n';
                was = true;
            }
            return;
        }
        // ставим открывающую:
        if (pattern[i] != ')') {
            s.push_back('(');
            dfs(i+1, balance+1);
            s.pop_back();
        }
        // ставим закрывающую:
        if (pattern[i] != '(' && balance > 0) {
            s.push_back(')');
            dfs(i+1, balance-1);
            s.pop_back();
        }
    };
    dfs(0, 0);
    if (!was)
        cout << "NO SOLUTION\n";
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
