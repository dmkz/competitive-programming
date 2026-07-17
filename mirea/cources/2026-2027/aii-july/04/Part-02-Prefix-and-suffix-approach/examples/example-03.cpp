// Пример: суффиксные суммы.
// Ввод: n и массив чисел.
// Вывод: массив суффиксных сумм длины n + 1.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<long long> suf(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << suf[i];
    }
    cout << '\n';

    return 0;
}