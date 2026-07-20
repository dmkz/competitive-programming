// Пример: сумма в каждом окне длины k.
// Ввод: n, k и массив a.
// Вывод: суммы всех окон длины k слева направо.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long window_sum = 0;
    // Сначала считаем сумму самого первого окна.
    for (int i = 0; i < k; i++) {
        window_sum += a[i];
    }

    for (int left = 0; left + k <= n; left++) {
        if (left > 0) {
            cout << ' ';
        }
        cout << window_sum;

        if (left + k < n) {
            // Убираем элемент, который ушёл слева, и добавляем новый справа.
            window_sum -= a[left];
            window_sum += a[left + k];
        }
    }
    cout << '\n';

    return 0;
}