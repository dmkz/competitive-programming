#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // будем отслеживать момент, когда перестановка станет тождественной
    // для этого можно поддерживать количество позиций, который равны индексу
    // и менять это количество
    int n; cin >> n;
    vector<int> p(n);
    int nEqual = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        nEqual += (p[i] == i);
    }
    int q; cin >> q;
    while (q --> 0) {
        // читаем данные запроса:
        int u, v; cin >> u >> v;
        --u, --v;
        // вычитаем неактуальную инфу:
        nEqual -= (p[u] == u);
        nEqual -= (p[v] == v);
        // меняем элементы:
        swap(p[u],p[v]);
        // добавляем актуальную инфу:
        nEqual += (p[u] == u);
        nEqual += (p[v] == v);
        // выводим ответ:
        cout << (nEqual == n ? "YES\n" : "NO\n");
    }
}
