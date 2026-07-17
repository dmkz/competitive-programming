// Пример: прибавление арифметической прогрессии на отрезке.
// Ввод: n, q и q запросов вида l r d.
// Вывод: итоговый массив после всех прибавлений.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // diff хранит второй разностный слой.
    vector<long long> diff(n + 3, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        long long d;
        cin >> l >> r >> d;

        long long len = r - l + 1;
        diff[l] += d;
        diff[r + 1] -= (len + 1) * d;
        diff[r + 2] += len * d;
    }

    // Первый префиксный проход восстанавливает наклон.
    vector<long long> a(n + 1, 0);
    long long current = 0;
    for (int i = 1; i <= n; i++) {
        current += diff[i];
        a[i] = current;
    }

    // Второй префиксный проход превращает наклон в итоговый массив.
    vector<long long> s(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + a[i];
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << s[i];
    }
    cout << '\n';

    return 0;
}