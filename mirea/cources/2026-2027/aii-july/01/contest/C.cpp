// Используем vector, чтобы обработать все запросы. Запрос "push x" - добавление в
// конец массива через push_back. Запрос "pop" - удаление с конца массива. Остался
// запрос "get i". Перечисляя элементы массива, мы обнаружим, что с какого-то момента
// элементы начнут повторяться - это и будет периодом повторения. Период равен текущей
// длине массива. В 0-индексации искомая позиция i-го элемента в массиве равна остатку
// от деления индекса на длину массива, то есть: a[(i-1) % a.size()].

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    int q; cin >> q;
    vector<int> a;
    while (q --> 0) {
        string s; cin >> s;
        if (s == "push") {
            // добавление элемента в конец:
            int x;
            cin >> x;
            a.push_back(x);
            cout << a.size() << '\n';
        } else if (s == "pop") {
            // удаление элемента из конца:
            int x = a.back();
            a.pop_back();
            cout << x << '\n';
        } else {
            // значение i-го элемента
            assert(s == "get");
            long long i;
            cin >> i;
            cout << a[(i-1) % a.size()] << '\n';
        }
    }
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
