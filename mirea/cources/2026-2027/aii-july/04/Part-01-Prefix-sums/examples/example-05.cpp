// Пример: построение префиксных сумм через std::exclusive_scan.
// Ввод: n и массив int.
// Вывод: массив префиксных сумм длины n + 1.

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Добавляем фиктивный ноль, чтобы получить pref длины n + 1.
    vector<int> extended = a;
    extended.push_back(0);

    vector<long long> pref(n + 1, 0);
    exclusive_scan(extended.begin(), extended.end(), pref.begin(), 0LL);

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << pref[i];
    }
    cout << '\n';

    return 0;
}