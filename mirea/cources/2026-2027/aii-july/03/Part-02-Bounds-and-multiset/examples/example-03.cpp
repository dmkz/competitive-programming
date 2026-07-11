#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
using namespace std;
using namespace __gnu_pbds;

template<typename T, typename Comp = std::less<T>>
using ordered_set = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;

void print(const string &name, const auto &a) {
    cout << name << " = {";
    int i = 0;
    for (int x : a) {
        if (i > 0) cout << ',';
        cout << x;
        i++;
    }
    cout << "}" << '\n';
}

int main() {
    ordered_set<int> s;

    // Вставка.
    s.insert(10);
    s.insert(3);
    s.insert(7);
    s.insert(15);
    s.insert(7);
    print("after insert", s);

    // find_by_order(i) возвращает итератор на i-й элемент.
    for (int i = 0; i < (int)s.size(); i++) {
        cout << "s[" << i << "] = " << *s.find_by_order(i) << '\n';
    }

    // Удаление.
    s.erase(10);
    print("after erase(10)", s);

    // Для int количество элементов на отрезке [L, R]
    // равно order_of_key(R + 1) - order_of_key(L).
    int L = 4;
    int R = 15;
    int cnt = s.order_of_key(R + 1) - s.order_of_key(L);
    cout << "count in [4, 15] = " << cnt << '\n';
}
