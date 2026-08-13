#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void setmax(auto& x, const auto& y) {
    // Заменяем значение, только если кандидат его улучшает.
    if (x < y) x = y;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем предметы и вместимость рюкзака:
    int n, c; cin >> n >> c;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++)
        cin >> w[i] >> v[i];
    // previous[x] хранит наибольшую ценность набора из уже обработанных предметов для вместимости x.
    vector<ll> previous(c + 1), current(c + 1);
    for (int i = 0; i < n; i++) {
        // Копируем варианты, в которых предмет i не входит в набор.
        current = previous;
        // Если взять предмет i, добавляем его ценность к оптимальному набору вместимости x - w[i].
        for (int x = w[i]; x <= c; x++)
            setmax(current[x], previous[x - w[i]] + v[i]);
        // Полученная строка описывает уже обработанные предметы на следующем шаге.
        swap(previous, current);
    }
    cout << previous[c] << '\n';
}