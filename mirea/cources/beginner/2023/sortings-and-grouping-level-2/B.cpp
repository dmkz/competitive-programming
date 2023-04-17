#include <bits/stdc++.h>
using namespace std;
int main() {
    // читаем данные:
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // отсортировать по убыванию (более точно по невозрастанию):
    sort(a.begin(), a.end(), greater<>());
    // взять максимумы пока не перевалим за m:
    for (int i = 0; i < n; i++) {
        // берём текущую флешку
        m -= a[i];
        // проверяем, набрали ли необходимый объём
        if (m <= 0) {
            cout << i+1 << '\n'; // выводим ответ
            break;
        }
    }
}