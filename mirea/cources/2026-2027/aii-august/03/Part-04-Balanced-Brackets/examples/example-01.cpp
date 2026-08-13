#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем количество пар скобок:
    int n; cin >> n;
    const int mod = 1000000007;
    // current[balance] хранит число правильных префиксов текущей длины с данным балансом.
    vector<int> current(n + 1), next(n + 1);
    // Пустой префикс с нулевым балансом можно получить единственным способом.
    current[0] = 1;
    // Каждый правильный префикс продолжаем одним допустимым символом.
    for (int pos = 0; pos < 2 * n; pos++) {
        // Для новой длины начинаем с недостижимых состояний.
        fill(next.begin(), next.end(), 0);
        for (int balance = 0; balance <= n; balance++) {
            // Из состояния, которому не соответствует ни одного префикса, переходов нет.
            if (current[balance] == 0) continue;
            // Открывающую скобку можно добавить, пока их количество не достигло n.
            if ((pos + balance) / 2 < n)
                next[balance + 1] = (next[balance + 1] + current[balance]) % mod;
            // Закрывающая скобка допустима, только если ранее была открыта парная скобка.
            if (balance > 0)
                next[balance - 1] = (next[balance - 1] + current[balance]) % mod;
        }
        // Префиксы новой длины становятся текущими.
        swap(current, next);
    }
    cout << current[0] << '\n';
}