// Напишем рекурсивный перебор, чтобы перебрать все 2^n вариантов расстановки знаков.
// Если мы ставим "+" перед a[i], то сумма увеличивается на a[i], иначе уменьшается.
// Если в самом конце получили ту сумму, которую хотели, то обновляем ответ.
// В данном решении текущая сумма не хранится. Вместо неё хранится величина, которую
// нам ещё осталось набрать.
#include <bits/stdc++.h>
using namespace std;
vector<int> a;
string s;
string answ;
int cnt;
void clear() {
    a = {};
    s = "";
    answ = "";
    cnt = 0;
}
void dfs(int i, int64_t x) {
    if (i == a.size()) {
        if (x == 0) { // нашли ответ
            cnt++;
            if (answ.empty())
                answ = s;
        }
        return;
    }
    // пробуем плюс
    s += '+';
    dfs(i+1, x - a[i]);
    s.pop_back();
    // пробуем минус
    s += '-';
    dfs(i+1, x + a[i]);
    s.pop_back();
}
void solve() {
    // читаем данные
    int n; int64_t x;
    cin >> n >> x;
    clear();
    a.resize(n);
    for (auto &it : a)
        cin >> it;
    dfs(0, x);
    if (cnt == 0) {
        cout << "0\nNO SOLUTION\n";
    } else {
        cout << cnt << '\n' << answ << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
