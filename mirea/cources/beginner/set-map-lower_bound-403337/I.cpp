#include <bits/stdc++.h>
using namespace std;
// 1. Запишем условие на равенство средних формально:
// sum / n == (sum - ai - aj) / (n-2)
// 2. Преобразуем, умножив крест-накрест:
// sum * (n-2) = n * (sum - ai - aj)
// 3. Раскроем скобки:
// sum * n - 2 * sum = sum * n - ai * n - aj * n
// 4. Сократим слагаемые:
// - 2 * sum = - ai * n - aj * n
// 5. Перенесём ai * n:
// ai * n = 2 * sum - aj * n
// Решение: переберём левую часть (n вариантов) и посчитаем,
// сколько равных ей правых частей. Правые части будем хранить
// в структуре данных map
void solve() {
    int n; cin >> n;
    int64_t sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    // вставляем величины (2 * sum - a[i] * 1LL * n) в map и считаем ответ
    map<int64_t, int> count;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        // сколько 2 * sum - a[j] * n, равных a[i] * n? (j < i)
        answ += count[a[i] * 1LL * n];
        // вставляем 2 * sum - a[i] * n:
        count[2 * sum - a[i] * 1LL * n]++;
    }
    cout << answ << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--) solve();
}