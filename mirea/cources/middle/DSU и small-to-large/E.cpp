#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; // cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        // создаём блоки из одного элемента:
        vector<list<int>*> blocks(1+n, nullptr);
        for (int i = 1; i <= n; i++) {
            blocks[i] = new list<int>{i};
        }
        // обрабатываем запросы:
        for (int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            if (blocks[u]->size() >= blocks[v]->size()) {
                // блок справа меньшего размера, поэтому мы перекладываем все элементы
                // из него в конец левого блока
                blocks[u]->insert(blocks[u]->end(), blocks[v]->begin(), blocks[v]->end());
                list<int> *needToDelete = blocks[v];
                for (auto vert : *blocks[v]) {
                    blocks[vert] = blocks[u];
                }
                delete needToDelete;
            } else {
                // блок слева меньшего размера, поэтому мы перекладываем все элементы
                // из него в начало правого блока
                blocks[v]->insert(blocks[v]->begin(), blocks[u]->begin(), blocks[u]->end());
                list<int> *needToDelete = blocks[u];
                for (auto vert : *blocks[u]) {
                    blocks[vert] = blocks[v];
                }
                delete needToDelete;
            }
        }
        // выводим все элементы получившегося блока:
        for (int v : *blocks[1]) cout << v << ' ';
        cout << '\n';
        delete blocks[1];
    }
    return 0;
}