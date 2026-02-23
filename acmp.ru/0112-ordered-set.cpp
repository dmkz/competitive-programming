// перестановки, инверсии, ordered_set
#include <bits/stdc++.h>
using namespace std;
// подключаем ordered_set!
#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag, tree_order_statistics_node_update>;
// set.find_by_order(k); <-- найти k-й элемент (порядковая статистика)
// set.order_of_key(x); <-- сколько элементов меньше чем x
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k; cin >> n >> k;
    int64_t answ{};
    for (int i = 0; i < k; i++) {
        ordered_set<int> s;
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            answ += int(j - s.order_of_key(x));
            s.insert(x);
        }
    }
    cout << answ << endl;
}
