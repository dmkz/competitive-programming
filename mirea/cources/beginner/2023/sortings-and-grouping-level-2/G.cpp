#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем исходные данные:
    int n0, n1, n01; // число только USB (тип 0), только PS/2 (тип 1), и обоих типов (тип 01)
    cin >> n0 >> n1 >> n01;
    int m; cin >> m;
    vector<pair<int,int>> a(m);
    for (auto &[price, t] : a) {
        string s; cin >> price >> s;
        t = (s != "USB");
    }
    // рассматриваем мыши в порядке возрастания цены
    // сначала покупаем мыши для тех, у кого только один порт
    // потом для тех, у кого два порта. В реальной жизни я бы делал точно также
    sort(a.begin(), a.end());
    int count{}; int64_t sum{};
    for (auto [price,t] : a) {
        const int before = n0+n1+n01;
        if (t == 0) { // USB-мышь
            if (n0 > 0) n0--;
            else if (n01 > 0) n01--;
        } else { // PS/2 мышь
            if (n1 > 0) n1--;
            else if (n01 > 0) n01--;
        }
        if (before > n0+n1+n01) // купили текущую мышь
            count++, sum+=price;
    }
    // выводим ответ:
    cout << count << ' ' << sum << '\n';
}