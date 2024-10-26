#include <bits/stdc++.h>
using namespace std;
void put(int x) {
    cout << "put " << x << endl;
}
int get() {
    cout << "get" << endl;
    int result; cin >> result;
    return result;
}
void solve() {
    // извлекаем все элементы из структуры
    int id = 0;
    while (true) {
        id++;
        if (id > 297) // если уже вытащили 297 элементов, то больше нет смысла
            break;
        if (get() == -1) // если элементы кончились
            break;
    }
    // кидаем 1, затем 2, затем вытаскиваем и смотрим, какой элемент вытащился
    put(1);
    put(2);
    if (get() == 1) cout << "queue" << endl;
    else cout << "stack" << endl;
}
main() {
    solve();
}
