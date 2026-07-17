// Пример: базовые префиксные суммы и ответы на запросы суммы на отрезке.
// Ввод: n, массив, q, затем q запросов [l, r] в единичной индексации.
// Вывод: сумма на каждом отрезке.

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

    // pref[i] хранит сумму первых i элементов.
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        cout << pref[r + 1] - pref[l] << '\n';
    }

    return 0;
}