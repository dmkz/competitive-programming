#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007;
int findNext(const string& p, int matched, char ch) {
    // В состоянии matched суффикс строки совпадает с префиксом p такой длины.
    string current = p.substr(0, matched) + ch;
    // Среди суффиксов current ищем самый длинный префикс шаблона.
    for (int len = min((int)p.size(), (int)current.size()); len >= 0; len--) {
        bool equal = true;
        // Проверяем, равен ли выбранный суффикс префиксу p той же длины.
        for (int i = 0; i < len; i++)
            if (current[current.size() - len + i] != p[i]) equal = false;
        // Перебор идёт по убыванию, поэтому первое совпадение задаёт новое состояние.
        if (equal) return len;
    }
    return 0;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем длину строящейся строки и запрещённый шаблон:
    int n; string p; cin >> n >> p;
    int m = p.size();
    // findNext слишком дорог для каждого перехода динамики, поэтому считаем таблицу один раз.
    vector<vector<int>> nextState(m, vector<int>(26));
    for (int matched = 0; matched < m; matched++)
        for (int ch = 0; ch < 26; ch++)
            nextState[matched][ch] = findNext(p, matched, char('a' + ch));
    // current[j] хранит число строк текущей длины без p, находящихся в состоянии j.
    vector<ll> current(m), next(m);
    // Пустая строка имеет состояние 0.
    current[0] = 1;
    for (int length = 0; length < n; length++) {
        // Добавляем по одной букве к каждой допустимой строке.
        fill(next.begin(), next.end(), 0);
        for (int matched = 0; matched < m; matched++) {
            for (int ch = 0; ch < 26; ch++) {
                int to = nextState[matched][ch];
                // Переход в m завершил шаблон, поэтому такую строку не учитываем.
                if (to == m) continue;
                next[to] = (next[to] + current[matched]) % mod;
            }
        }
        // Полученный слой описывает строки следующей длины.
        swap(current, next);
    }
    ll answ = 0;
    // Складываем все безопасные конечные состояния.
    for (auto it : current)
        answ = (answ + it) % mod;
    cout << answ << '\n';
}