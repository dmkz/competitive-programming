// Пример: один и тот же шаблон push_back для префиксов и суффиксов.
// Ввод: n и массив.
// Вывод: сначала префиксные суммы, потом суффиксные суммы по длине.

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

    // Один и тот же интерфейс: меняется только направление обхода.
    vector<long long> pref = {0};
    for (int i = 0; i < n; i++) {
        pref.push_back(pref.back() + a[i]);
    }

    vector<long long> suff_len = {0};
    for (int i = n - 1; i >= 0; i--) {
        suff_len.push_back(suff_len.back() + a[i]);
    }

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << pref[i];
    }
    cout << '\n';

    for (int i = 0; i <= n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << suff_len[i];
    }
    cout << '\n';

    return 0;
}