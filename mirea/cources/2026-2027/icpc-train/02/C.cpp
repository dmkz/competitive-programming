#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using ll = long long;
// решение задачи:
void solve() {
    int b; string d, n;
    cin >> b >> d >> n;
    // если n состоит целиком из > максимальных цифр, то ответ имеет длину |n|+1
    if (n > string(n.size(), d.back())) {
        string answ(n.size() + 1, d.front());
        if (d.front() == '0') {
            if (d.size() > 1)
                answ.front() = d[1];
            else
                answ = "-1";
        }
        cout << answ << '\n';
        return;
    }
    // иначе ответ имеет такую же длину, строим его слева-направо
    string answ(n.size(), d.front());
    for (int i = 0; i < (int)n.size(); i++) {
        auto it = lower_bound(d.begin(), d.end(), n[i]);
        if (it == d.end()) {
            // не нашлось цифры, пытаемся увеличить предыдущие разряды
            while (i > 0 && answ[i-1] == d.back()) i--;
            assert(i > 0);
            auto jt = upper_bound(d.begin(), d.end(), answ[i-1]);
            assert(jt != d.end());
            answ[i-1] = *jt;
            fill(answ.begin()+i, answ.end(), d.front());
            break;
        }
        // иначе ставим найденную цифру:
        answ[i] = *it;
        if (*it > n[i]) break;
    }
    cout << answ << "\n";
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
