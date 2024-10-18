#include <bits/stdc++.h>
using namespace std;
main() {
    // читаем данные
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    vector<int> d(n);
    for (int i = 0; i < n; i++)
        cin >> d[i];
    // решаем задачу
    multiset<int, greater<int>> opened;
    multiset<int> closed;
    int64_t answ = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            // открывается новая скобка
            opened.insert(d[i]);
        } else {
            // закрывается скобка
            // сначала попробуем ей в пару поставить максимальную из открытых
            if (opened.size()) {
                auto it = opened.begin();
                answ += (*it + d[i]);
                closed.insert(d[i]);
                opened.erase(it);
            } else {
                // иначе пробуем заменить одну из уже использованных закрывающихся скобок
                // нашей текущей скобкой, если замена будет выгодной
                if (closed.size() && *closed.begin() < d[i]) {
                    answ += (d[i] - *closed.begin());
                    closed.erase(closed.begin());
                    closed.insert(d[i]);
                }
            }
        }
    }
    cout << answ << endl;
}
