#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив и запоминаем позиции каждого элемента
    // будем использовать 1-индексацию, так как лень вычитать 1
    int n; cin >> n;
    vector<int> a(1+n), pos(1+n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    // начинаем ставить элементы на место начиная с самого первого
    vector<pair<int,int>> answer;
    for (int i = 1; i <= n; i++)
        if (a[i] != i) {
            // надо поставить элемент i на позицию i
            // где он сейчас? На pos[i]. Свапаем и обновляем позиции
            int j = pos[i];
            swap(a[i], a[j]);
            pos[a[i]] = i;
            pos[a[j]] = j;
            answer.emplace_back(i, j);
        }
    // выводим ответ:
    cout << answer.size() << "\n";
    for (auto [i, j] : answer)
        cout << i << ' ' << j << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
