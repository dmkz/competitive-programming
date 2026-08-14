#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем команды и нужный точный вес:
    int q, c; cin >> q >> c;
    vector<int> weight(q + 1);
    vector<ll> ways(c + 1);
    // ways[x] хранит количество подмножеств из активных предметов с точным весом x.
    // Пустое подмножество – единственное подмножество с весом 0.
    ways[0] = 1;
    for (int queryId = 1; queryId <= q; queryId++) {
        char type; int value; cin >> type >> value;
        if (type == '+') {
            // Запоминаем вес предмета по номеру команды, чтобы найти его при удалении.
            weight[queryId] = value;
            // При добавлении предмета с весом value подмножество с весом x - value получает вес x.
            // При обходе справа налево читаем состояния до добавления предмета.
            for (int x = c; x >= value; x--)
                ways[x] = (ways[x] + ways[x - value]) % mod;
        } else {
            int w = weight[value];
            // После удаления вычитаем подмножества, в которые входил предмет с весом w.
            // При обходе слева направо читаем состояния, уже восстановленные до удаления предмета.
            for (int x = w; x <= c; x++)
                ways[x] = (ways[x] - ways[x - w] + mod) % mod;
        }
        cout << ways[c] << '\n';
    }
}