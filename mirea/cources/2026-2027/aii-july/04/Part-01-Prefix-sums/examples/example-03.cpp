// Пример: безопасное использование std::partial_sum для префиксных сумм.
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

    // partial_sum накапливает в типе входного диапазона,
    // поэтому сначала переводим данные в long long.
    vector<long long> a64(a.begin(), a.end());
    vector<long long> pref(n + 1, 0);
    partial_sum(a64.begin(), a64.end(), pref.begin() + 1);

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << pref[i];
    }
    cout << '\n';

    return 0;
}