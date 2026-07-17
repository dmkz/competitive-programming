// Пример: сумма положительных чисел на отрезке.
// Читает массив и запросы [l, r] в единичной индексации.
// Для каждого запроса выводит сумму положительных элементов на отрезке.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Считываем размер массива и число запросов.
    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // pref_pos[i] хранит сумму положительных элементов среди первых i чисел.
    vector<long long> pref_pos(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref_pos[i + 1] = pref_pos[i];
        if (a[i] > 0) {
            pref_pos[i + 1] += a[i];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        // Сумма на отрезке берётся как разность двух префиксов.
        cout << pref_pos[r + 1] - pref_pos[l] << '\n';
    }

    return 0;
}