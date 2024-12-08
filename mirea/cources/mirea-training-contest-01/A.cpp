#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // сортируем
    sort(a.begin(), a.end());
    // формируем скобки по 2 числа
    // объединяя максимумы с минимумами
    int64_t sum{};
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int64_t s = a[i] + a[j];
        sum += s * s;
    }
    cout << sum << endl;
}
