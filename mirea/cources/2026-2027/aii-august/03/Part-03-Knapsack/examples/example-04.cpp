#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем веса предметов и нужный точный вес:
    int n, c; cin >> n >> c;
    vector<int> w(n);
    for (auto& it : w)
        cin >> it;
    // previous[x] хранит количество подмножеств с весом x из уже обработанных предметов.
    vector<ll> previous(c + 1), current(c + 1);
    // Пустое подмножество – единственное подмножество с весом 0.
    previous[0] = 1;
    for (int i = 0; i < n; i++) {
        // Сначала копируем подмножества, в которые предмет i не входит.
        current = previous;
        // Если взять предмет i, к подмножеству с весом x - w[i] добавляется этот предмет.
        for (int x = w[i]; x <= c; x++)
            current[x] += previous[x - w[i]];
        // Полученная строка описывает уже обработанные предметы на следующем шаге.
        swap(previous, current);
    }
    cout << previous[c] << '\n';
}