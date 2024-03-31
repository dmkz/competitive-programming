#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
void solve() {
    // читаем строку:
    int n; cin >> n;
    string s; cin >> s;
    // ищем максимальный символ:
    int maxChar = 'a';
    for (auto it : s)
        if (maxChar < it)
            maxChar = it;
    // выводим его номер в алфавите:
    cout << (maxChar - 'a' + 1) << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t --> 0)
        solve();
}
