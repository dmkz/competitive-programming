#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        // создаём блоки из одного элемента:
        vector<list<int>> blocks(1+n);
        vector<int> id(1+n);
        for (int i = 1; i <= n; i++) {
            blocks[i] = {i};
            id[i] = i;
        }
        // обрабатываем запросы:
        for (int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            int iu = id[u];
            int iv = id[v];
            if (blocks[iu].size() >= blocks[iv].size()) {
                // блок справа меньшего размера, поэтому мы перекладываем все элементы
                // из него в конец левого блока
                blocks[iu].insert(blocks[iu].end(), blocks[iv].begin(), blocks[iv].end());
                for (auto vert : blocks[iv]) {
                    id[vert] = iu;
                }
                blocks[iv].clear();
            } else {
                // блок слева меньшего размера, поэтому мы перекладываем все элементы
                // из него в начало правого блока
                blocks[iv].insert(blocks[iv].begin(), blocks[iu].begin(), blocks[iu].end());
                for (auto vert : blocks[iu]) {
                    id[vert] = iv;
                }
                blocks[iu].clear();
            }
        }
        // выводим все элементы получившегося блока:
        for (int v : blocks[id[1]]) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}