#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    int n; cin >> n;
    // сначала разрежем строку по буквам W
    // каждую такую часть нужно будет закрашивать независимо
    vector<string> parts = {""};
    for (int i = 0; i < n; i++) {
        char ch; cin >> ch;
        if (ch == 'W') {
            // текущая часть заканчивается, начинается новая
            parts.push_back("");
        } else {
            // символ добавляется к последней части
            parts.back() += ch;
        }
    }
    // теперь проверяем каждую часть отдельно
    bool ok = true;
    for (const auto &s : parts) {
        // часть можно получить, если её длина = 0 или >= 2 и
        // есть как буква R, так и буква B
        if (s.size() == 1u) {
            ok = false;
            break;
        }
        if (s.size() >= 2u)
            ok &= (count(all(s), 'R') > 0) && (count(all(s), 'B') > 0);
    }
    cout << (ok ? "YES\n" : "NO\n");
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
