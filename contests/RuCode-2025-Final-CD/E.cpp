// Задача: E, Вердикт: OK, Время: 0.013 сек, Память: 2 MB

// EF должно быть делителем числа n (по условию задачи). Найдём все делители
// числа n и проверим каждый из них. При проверке мы знаем, что EF = 14 * base + 15,
// поэтому мы должны найти base. Зафиксировав делитель, base находится однозначно.

#include <bits/stdc++.h>
#define int int64_t
using namespace std;

// факторизация числа n за время O(sqrt(n))
vector<int> factor(int n) {
    // переберём делители до корня из n. В вектор lowerHalf запишем делители
    // меньше корня, а в upperHalf - больше корня
    vector<int> lowerHalf, upperHalf;
    for (int x = 1; x * x <= n; x++)
        if (n % x == 0) {
            int y = n / x;
            lowerHalf.push_back(x);
            if (y != x)
                upperHalf.push_back(y);
        }
    // объединяя обе половины, получаем полный список делителей
    while (upperHalf.size()) {
        lowerHalf.push_back(upperHalf.back());
        upperHalf.pop_back();
    }
    return lowerHalf;
}
const int inf = (int)1e18L;
main() {
    // переберём делители числа
    int n; cin >> n;
    int minBase = inf;
    for (int x : factor(n)) {
        // Число EF = 14 * base + 15. Нужно найти base.
        // Предположим, что EF = x (текущему делителю), тогда выразим base:
        // x = 14 * base + 15
        // (x - 15) / 14 = base
        int base = (x - 15) / 14;
        // проверка что наше решение подошло:
        if (base >= 16 && 14 * base + 15 == x) {
            // обновляем лучший ответ:
            minBase = min(minBase, base);
        }
    }
    // выводим ответ, корректно обрабатывая случай с -1:
    if (minBase >= inf)
        minBase = -1;
    cout << minBase << endl;
}
