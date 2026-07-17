// Пример: разностный массив для прибавлений на отрезках.
// Ввод: n, q и q операций вида l r x.
// Вывод: итоговый массив после всех операций.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // В массиве a накапливаем запланированные изменения.
    vector<long long> a(n + 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        long long x;
        cin >> l >> r >> x;
        --l;
        --r;
        a[l] += x;
        if (r + 1 < n) {
            a[r + 1] -= x;
        }
    }

    // После этого один раз считаем префиксные суммы и получаем итоговый массив s.
    vector<long long> s(n);
    long long current = 0;
    for (int i = 0; i < n; i++) {
        current += a[i];
        s[i] = current;
    }

    for (int i = 0; i < n; i++) {
        if (i) {
            cout << ' ';
        }
        cout << s[i];
    }
    cout << '\n';

    return 0;
}