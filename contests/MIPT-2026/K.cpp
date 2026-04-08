// конструктив, инварианты, чётность, перемещения на плоскости
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем доступные перемещения и считаем количество чётных:
    int k; cin >> k;
    vector<int> a(k);
    int cntEven = 0;
    for (auto &it : a) {
        cin >> it;
        cntEven += (it % 2 == 0);
    }
    int x, y; cin >> x >> y;
    if (cntEven > 0) {
        // если есть чётное, то можем получить любой вектор. Сначала:
        // (0, 2) и (2, 0). Затем (1, 0) и (0, 1).
        cout << "Yes\n";
    } else if (abs(x) % 2 == abs(y) % 2) {
        // если все перемещения нечётные, то любой вектор (a, 1)
        // меняет чётность обоих компонент - инвариант. Поэтому Yes, // если у них одинаковая чётность
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
