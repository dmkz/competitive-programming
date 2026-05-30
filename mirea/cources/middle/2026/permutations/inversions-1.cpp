#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,
                         tree_order_statistics_node_update>;
// s.find_by_order(k)  <-- найти k-й по порядку элемент
// s.order_of_key(x) <-- найти, на какую позицию встанет число x

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    ordered_set<int> s;
    for (int i = 0; i < n; i++) {
        int pi; cin >> pi;
        cout << s.size() - s.order_of_key(pi) << endl;
        s.insert(pi);
    }
    cout << endl;
}