// Пример: суффиксные суммы с индексацией позицией начала суффикса.
// Ввод: n и массив.
// Вывод: массив suff длины n + 1.

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

    vector<long long> suff(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suff[i] = suff[i + 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << suff[i];
    }
    cout << '\n';

    return 0;
}