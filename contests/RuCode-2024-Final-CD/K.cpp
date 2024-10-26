#include <bits/stdc++.h>
using namespace std;
using ll = long long;
char ask(ll x) {
    cout << "? " << x << endl;
    char ch; cin >> ch;
    return ch;
}
main() {
    ll maxw; cin >> maxw;
    // спрашиваем первую
    ll prev = 0;
    vector<tuple<char,ll,ll>> g;
    while (prev < maxw) {
        char c = ask(prev+1);
        // запускаем бинпоиск
        ll low = prev+1, high = maxw+1;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            char t = ask(mid);
            if (t == c)
                low = mid;
            else
                high = mid;
        }
        // группа
        g.emplace_back(c, prev+1, low);
        prev = low;
    }
    cout << "!";
    for (const auto &[c,_,max] : g)
        cout << " " << c << " " << max;
    cout << endl;
}
