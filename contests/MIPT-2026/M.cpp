// инверсии, конструктив, перестановки, математика, ordered_set
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
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
    // читаем данные, запоминаем позиции элементов и считаем кол-во
    // операций, чтобы получить [1, 2, 3, ..., n]:
    int n; cin >> n;
    vector<int> a(n), pos(n+1);
    ordered_set<int> s;
    int64_t sum{};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
        sum += int(s.size() - s.order_of_key(a[i]));
        s.insert(a[i]);
    }
    // перекидывая по одному элементу из конца в начало, получаем ответ:
    int64_t answ = sum;
    for (int x = n; x >= 2; x--) {
        // раньше элемент x двигался в конец:
        sum -= n-1-pos[x];
        // теперь он двигается в начало:
        sum += pos[x];
        // обновляем ответ:
        if (answ > sum)
            answ = sum;
    }
    cout << answ << endl;
}
