#include <bits/stdc++.h>
using namespace std;
using ld = long double;
main() {
    // чтение данных
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    // бинарный поиск по ответу: sum(a[i]) / sum(b[i]) >= mid
    // преобразуем: sum(a[i]) >= mid * sum(b[i])
    // переносим всё влево: sum(a[i]) - mid * sum(b[i]) >= 0
    // вносим mid под знак суммы: sum(a[i] - mid * b[i]) >= 0
    // надо набрать k максимумов вида a[i] - mid * b[i] и проверить их
    ld low = 0, high = 1e6+1;
    while (high - low > 1e-10) {
        ld mid = (low + high) / 2;
        // строим массив c[i] = a[i] - x * b[i]
        vector<ld> c(n);
        for (int i = 0; i < n; i++)
            c[i] = a[i] - mid * b[i];
        // сортируем по убыванию:
        sort(c.begin(), c.end(), greater<>());
        // оставляем k максимумов:
        c.resize(k);
        // находим их сумму:
        auto sum = accumulate(c.begin(), c.end(), 0.0);
        // смещаем границу бинпоиска:
        if (sum >= 0) low = mid; // можем
        else high = mid; // не можем
    }
    // выводим ответ
    cout << fixed << setprecision(12);
    cout << low << endl;
}
