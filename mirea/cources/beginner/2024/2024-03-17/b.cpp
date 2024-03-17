#include <bits/stdc++.h>
using namespace std;
void solve() {
    // строки = в красный
    // столбцы = в синий
    // надо проверить, есть ли строка, состоящая целиком из букв R
    // или есть ли столбец, состоящий целиком из букв B
    // чтение поля:
    int n = 8;
    vector<string> a(n);
    for (auto &it : a)
        cin >> it;
    bool lastWasRed = false;
    for (const auto &it : a)
        // хотя бы одна строка целиком равна n буквам R
        lastWasRed |= (it == string(n, 'R'));
    cout << (lastWasRed ? 'R' : 'B') << "\n";
}
int main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
