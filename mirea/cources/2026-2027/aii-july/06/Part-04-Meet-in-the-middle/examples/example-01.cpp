// Пример: максимальная сумма подмножества, не превосходящая limit_sum.
// Для малого n просто перебираем все маски.

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    long long limit_sum;
    // Считываем массив и ограничение на сумму.
    cin >> n >> limit_sum;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Перебираем все подмножества битовой маской.
    long long best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long current_sum = 0;
        for (int i = 0; i < n; i++) {
            // Бит i показывает, берём ли элемент a[i].
            if ((mask >> i) & 1) current_sum += a[i];
        }
        if (current_sum <= limit_sum) {
            best = max(best, current_sum);
        }
    }

    // Печатаем лучшую допустимую сумму.
    cout << best << '\n';
    return 0;
}