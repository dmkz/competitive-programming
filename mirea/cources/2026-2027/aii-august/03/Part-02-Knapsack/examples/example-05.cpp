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
    // ways[x] хранит количество подмножеств с весом x, составленных из уже обработанных предметов.
    vector<ll> ways(c + 1);
    // Пустое подмножество – единственное подмножество с весом 0.
    ways[0] = 1;
    for (int i = 0; i < n; i++) {
        // Если взять предмет i, он дополняет подмножество с весом x - w[i] до веса x.
        // Обратный обход читает состояние, в котором предмет i ещё не был добавлен.
        for (int x = c; x >= w[i]; x--)
            ways[x] += ways[x - w[i]];
    }
    cout << ways[c] << '\n';
}