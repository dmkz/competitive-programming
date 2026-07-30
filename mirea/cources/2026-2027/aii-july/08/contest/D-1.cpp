// Будем поддерживать множество элементов в порядке возрастания, но хранить отдельно его
// левую и правую половины. Тогда медиана будет стоять в конце левой половины. Перед вставкой
// нового элемента мы сначала определяем, в какую половину он попадает, вставляем в неё, а
// затем мы делаем размеры половин примерно равными, перекидывая из начала правой половины в
// конец левой, или из конца левой половины в начало правой.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    set<int> left, right;
    auto insertAndRebalance = [&](int x) {
        // функция вставляет элемент и приводит баланс между размерами половин в порядок
        // половины уже отсортированы. Нужно определить, куда попадает x, и вставить его:
        if (left.size() && x <= *left.rbegin())
            left.insert(x);
        else
            right.insert(x);
        // перекидываем из левой половины в правую:
        while (left.size() > right.size()+1) {
            right.insert(*left.rbegin());
            left.erase(--left.end());
        }
        // перекидываем из правой половины в левую:
        while (right.size() > left.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    };
    // читаем данные и вставляем их в множество:
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        insertAndRebalance(x);
    }
    // обрабатываем запросы:
    while (q --> 0) {
        int x; cin >> x;
        insertAndRebalance(x);
        cout << *left.rbegin() << ' ';
    }
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
