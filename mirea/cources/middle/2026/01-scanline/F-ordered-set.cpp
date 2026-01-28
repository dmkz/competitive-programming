#include <bits/stdc++.h>
using namespace std;
// подключаем ordered_set:
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;
// set.find_by_order(k); <-- найти k-й элемент (порядковая статистика)
// set.order_of_key(x); <-- сколько элементов меньше чем x
main() {
    // читаем данные и создаём события:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tuple<int,int,int>> events(n);
    for (int i = 0; auto &[l, r, id] : events) {
        cin >> l >> r;
        id = i++;
    }
    // сортируем их в порядке возрастания левой границы:
    sort(events.begin(), events.end());
    // обрабатываем с конца в начало, считая для каждого отрезка
    // количество отрезков, которые в него вложены. Для этого
    // мы храним в ordered_set правые границы отрезков, которые
    // находятся правее текущего отрезка, и спрашиваем, сколько
    // из них меньше, чем правая граница текущего отрезка
    ordered_set<int> ends;
    vector<int> answer(n);
    for (int i = n-1; i >= 0; i--) {
        auto [_, r, id] = events[i];
        answer[id] = (int)ends.order_of_key(r);
        ends.insert(r);
    }
    // выводим ответы:
    for (auto it : answer)
        cout << it << ' ';
    cout << endl;
}
