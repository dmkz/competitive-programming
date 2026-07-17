// Пример: построение префиксных сумм через std::inclusive_scan.
// Ввод: n и массив int.
// Вывод: массив префиксных сумм длины n + 1.

#include <functional>
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

    // Благодаря 0LL накопление выполняется в long long.
    vector<long long> pref(n + 1, 0);
    inclusive_scan(a.begin(), a.end(), pref.begin() + 1, plus<long long>(), 0LL);

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << pref[i];
    }
    cout << '\n';

    return 0;
}