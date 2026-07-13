// Моделируем запросы к очереди. Используем структуру данных queue.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    int nQ; cin >> nQ;
    queue<int> q;
    while (nQ --> 0) {
        char c; cin >> c;
        if (c == '+') {
            // добавление элемента в конец очереди:
            int x;
            cin >> x;
            q.push(x);
        } else {
            assert(c == '-');
            // вывод первого элемента в очереди и его удаление:
            cout << q.front() << '\n';
            q.pop();
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
