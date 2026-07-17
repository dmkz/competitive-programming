// Пример: восстановление массива по известным префиксным суммам.
// Ввод: n и массив pref длины n + 1.
// Вывод: исходный массив a.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> pref(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> pref[i];
    }

    // Каждый элемент равен разности двух соседних префиксов.
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = pref[i + 1] - pref[i];
    }

    for (int i = 0; i < n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}