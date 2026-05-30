#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T, typename Comp = less<T>>
using ordered_set = tree<T, null_type, Comp, rb_tree_tag,
                         tree_order_statistics_node_update>;
// x = s.find_by_order(k) = s[k] <-- найти k-й по порядку элемент
// k = s.order_of_key(x) <-- найти, на какую позицию встанет число x

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<int> cnt(n);
    ordered_set<int, greater<int>> s;
    for (int i = 0; i < n; i++) {
        cin >> cnt[i];
        s.insert(i+1);
    }
    // восстанавливаем ответ:
    vector<int> answ(n);
    for (int i = n-1; i >= 0; i--) {
        // всего осталось i элементов
        // среди них cnt[i] больше чем i-й
        answ[i] = *s.find_by_order(cnt[i]);
        s.erase(answ[i]);
    }
    // выводим ответ:
    for (int i = 0; i < n; i++)
        cout << answ[i] << ' ';
    cout << endl;
}