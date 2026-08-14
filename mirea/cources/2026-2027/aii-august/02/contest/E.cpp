// Запишем формальное условие. Мы можем сделать прыжок i --> j, если верно следующее:
// i < j и y[j] - y[i] < x[j] - x[i]. Преобразуем неравенство путём переноса того, что зависит
// от i, налево, а того, что зависит от j, направо. Получим: x[i] - y[i] < x[j] - y[j].
// Обозначим A[i] = x[i] - y[i]. Тогда нужно найти наибольшую возрастающую последовательность
// в массиве A и восстановить её элементы.
#include <bits/stdc++.h>
using namespace std;
const int inf = (int)2e9+100;
using pii = pair<int,int>;
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    for (int i = 0; i < n; i++)
        cin >> y[i];
    // Формальное условие: y[j] - y[i] < x[j] - x[i] => x[i] - y[i] < x[j] - y[j]
    // Обозначим a[i] = x[i] - y[i]. Тогда для массива "a" нужно найти максимальную
    // возрастающую подпоследовательность и вывести индексы входящих в неё элементов
    vector<int> a(n), prev(n, -1);
    vector<pii> dp(n+1, {inf, inf});
    dp[0] = {-inf, -1};
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), pii{x[i] - y[i], -inf});
        prev[i] = (it-1)->second;
        *it = {x[i] - y[i], i};
    }
    // находим длину НВП:
    int len = n;
    while (len >= 0 && dp[len].first == inf)
        len--;
    // восстанавливаем индексы входящих в неё элементов:
    vector<int> answ;
    for (int i = dp[len].second; i > -1; i = prev[i])
        answ.push_back(i);
    reverse(answ.begin(), answ.end());
    // выводим ответ:
    cout << len << '\n';
    for (auto it : answ)
        cout << it+1 << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
