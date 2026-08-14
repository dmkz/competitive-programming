// Нужно разбить массив на группы. Количество групп не ограничено. Снова будем решать справа
// налево, потому что так будет удобнее писать формулы перехода и восстанавливать ответ.
// Пусть dp[i] = минимальная стоимость разбиения суффикса [i, i+1, ..., n] на группы.
// Инициализация: dp[n] = 0 - пустой суффикс получаем бесплатно.
// Переходы: перебираем границы группы, в которую мы включим i-й элемент. Пусть это [i, j].
// Тогда dp[i] = min(cost(i, j) + dp[j+1]), означающая, что мы сформировали группу [i, j], а
// затем продолжили формировать группы, начиная с (j+1)-го элемента.
// cost(i, j) = (max(a[i..j]) - min(a[i..j]))^2 + c. Можно предподсчитать заранее, либо
// считать вместе с динамикой на лету.
// Для восстановления ответа храним пару (значение, индекс последнего элемента).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 8e18L;
void solve() {
    // читаем данные
    int n, c; cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // решаем задачу справа-налево для удобства
    vector dp(n+1, pair<ll,int>(inf, -1));
    dp[n] = {0, -1};
    for (int i = n - 1; i >= 0; i--) {
        int minA = a[i], maxA = a[i];
        for (int j = i; j < n; j++) {
            // включаем отрезок [i, j] и добавляем к нему dp[j+1]
            if (minA > a[j]) minA = a[j];
            if (maxA < a[j]) maxA = a[j];
            ll currCost = (maxA - minA) * 1LL * (maxA - minA) + c;
            dp[i] = min(dp[i], make_pair(dp[j+1].first + currCost, j));
        }
    }
    // восстанавливаем ответ:
    vector<int> answ;
    for (int i = 0; i < n; i = dp[i].second + 1)
        answ.push_back(dp[i].second);
    // выводим его:
    cout << dp[0].first << '\n';
    cout << answ.size() << '\n';
    for (auto it : answ)
        cout << it + 1 << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
