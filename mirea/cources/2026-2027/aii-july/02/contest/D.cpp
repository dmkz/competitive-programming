// Для решения задачи будем хранить две половины в очереди в двух разных deque.
// Если обеспечим равенство размеров половин, то вставка в середину означает добавление
// в конец первой очереди. Вставка в конец - добавление в конец второй очереди.
// Извлечение элемента - из начала первой очереди. После каждого запроса уравниваем
// размеры двух половин: если правая половина больше, то перекидываем элемент из её
// начала в конец левой половины, а если левая половина больше - то из её конца в начало
// правой половины.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
void solve() {
    deque<int> left, right;
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == '+') {
            // кладём в конец очереди:
            int x; cin >> x;
            right.push_back(x);
        } else if (c == '*') {
            // кладём в середину очереди:
            int x; cin >> x;
            left.push_back(x);
        } else {
            assert(c == '-');
            // вынимаем элемент из головы очереди:
            cout << left.front() << '\n';
            left.pop_front();
        }
        // после выполнения запроса поддерживаем примерно равный размер половин:
        while (left.size() < right.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
        while (left.size() > right.size()+1) {
            right.push_front(left.back());
            left.pop_back();
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
