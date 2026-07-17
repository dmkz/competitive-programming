// Пример: два слоя предобработки.
// Ввод: n, m, k, q; затем m отрезков и q запросов.
// Вывод: для каждого запроса число позиций, покрытых хотя бы k отрезками.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, q;
    cin >> n >> m >> k >> q;

    // В массиве a накапливаем, где покрытие начинается и где заканчивается.
    vector<int> a(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        a[l] += 1;
        if (r + 1 < n) {
            a[r + 1] -= 1;
        }
    }

    // Строим бинарный массив good: хорошая ли позиция.
    vector<int> g(n, 0);
    int current = 0;
    for (int i = 0; i < n; i++) {
        current += a[i];
        if (current >= k) {
            g[i] = 1;
        }
    }

    // Поверх good строим ещё одни префиксные суммы.
    vector<int> h(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h[i + 1] = h[i] + g[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        cout << h[r + 1] - h[l] << '\n';
    }

    return 0;
}