#include <bits/stdc++.h>
using namespace std;
void solve() {
    // посчитаем количество каждого числа и найдём то, которое встречается
    // 3 или более раз
    int n; cin >> n;
    map<int, int> count;
    int answer = -1;
    while (n --> 0) {
        int number; cin >> number;
        count[number]++;
        if (count[number] >= 3)
            answer = number;
    }
    cout << answer << "\n";
}
main() {
    // ускорение ввода-вывода
    ios::sync_with_stdio(false);
    cin.tie(0);
    // мультитесты
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
