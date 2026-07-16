// Данное решение работает за линейное времян - за O(n+q). Мы храним одновременно:
// 1) стек из элементов;
// 2) стек на минимум;
// 3) стек на максимум;
// 4) хеш-таблицу с количеством каждого элемента.
// Из хеш-таблицы удаляем значения, когда их количество достигло нуля. Таким образом,
// размер хеш-таблицы и будет количеством различных элементов. А минимум и максимум
// берём с верхушки стеков.
#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000007;
void solve() {
    // читаем данные
    int n; cin >> n;
    unordered_map<int, int> cnt;
    stack<int> stVal, stMin, stMax;
    // добавим бесконечности:
    stVal.push(inf);
    stMin.push(+inf);
    stMax.push(-inf);
    // теперь добавим нормальные элементы:
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        stVal.push(x);
        stMin.push(min(stMin.top(), x));
        stMax.push(max(stMax.top(), x));
        cnt[x]++;
    }
    // обрабатываем запросы
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == '+') {
            int x; cin >> x;
            stVal.push(x);
            stMin.push(min(stMin.top(), x));
            stMax.push(max(stMax.top(), x));
            cnt[x]++;
        } else if (c == '?') {
            cout << stMin.top() << ' ' << stMax.top() << ' ' << cnt.size() << '\n';
        } else if (c == '-') {
            // сначала удалим из стека:
            int last = stVal.top();
            stVal.pop(); stMin.pop(); stMax.pop();
            // теперь аккуратно удалим из хеш-таблицы:
            auto iter = cnt.find(last);
            iter->second--; // уменьшаем количество
            if (iter->second == 0) // стало равным нулю => удаляем
                cnt.erase(iter);
        }
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
