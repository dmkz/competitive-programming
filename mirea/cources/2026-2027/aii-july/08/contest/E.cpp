// Если мы обозначим ход первого игрока как "0", а ход второго как "1", то последовательность
// ходов в игре однозначно кодируется бинарной строкой длины "2n", содержащей "n" нулей и "n"
// единиц. Рекурсивно переберём все двоичные строки, проверяя, может ли выбранный игрок
// сделать ход: для этого сравниваем чётность его числа и числа на столе.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массивы
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto &it : a) cin >> it;
    for (auto &it : b) cin >> it;
    // запускаем рекурсию
    int64_t answ = 0;
    vector<int> c;
    function<void(int,int)> dfs = [&](int n1, int n2) {
        // если элементы закончились, выходим из рекурсии:
        if (n1 == 0 && n2 == 0) {
            answ++;
            return;
        }
        // пытаемся взять из первого массива:
        if (n1 > 0 && (c.empty() || abs(c.back()) % 2 != abs(a[n1-1]) % 2)) {
            c.push_back(a[n1-1]);
            dfs(n1-1, n2);
            c.pop_back();
        }
        // пытаемся взять из второго массива:
        if (n2 > 0 && (c.empty() || abs(c.back()) % 2 != abs(b[n2-1]) % 2)) {
            c.push_back(b[n2-1]);
            dfs(n1, n2-1);
            c.pop_back();
        }
    };
    // вызываем рекурсивную функцию:
    dfs(n, n);
    // выводим ответ:
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
