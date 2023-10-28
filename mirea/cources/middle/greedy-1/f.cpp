#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vvi next(1+n);
    for (int u = 2, parent; u <= n; ++u) {
        cin >> parent;
        next[parent].push_back(u);
    }
    // для каждой вершины дерева посчитаем количество листьев в её поддереве
    vi countLeafs(1+n);
    function<void(int,int)> calc = [&](int u, int p) {
        countLeafs[u] = (int)next[u].empty();
        for (int v : next[u]) {
            if (p == v) continue;
            calc(v, u);
            countLeafs[u] += countLeafs[v];
        }
    };
    calc(1, 0);
    // используем тот факт, что для двух поддеревьев множества листьев:
    // либо меньшее является подмножеством большего
    // либо множества не пересекаются вообще
    // тогда k-й ответ это k-е по возрастанию число в массиве кол-ва листьев
    // сортируем и выводим ответы
    vi a;
    for (int i = 1; i <= n; ++i)
        a.push_back(countLeafs[i]);
    sort(all(a));
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << endl;
}
