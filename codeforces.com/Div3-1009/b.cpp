#include <bits/stdc++.h>
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // будем два минимума извлекать и добавлять min1+min2-1
        int n; std::cin >> n;
        std::multiset<int> a;
        for (int i = 0; i < n; i++) {
            int x; std::cin >> x;
            a.insert(x);
        }
        // пока у нас больше одного элемента
        while (a.size() > 1) {
            // первый минимум:
            auto min1 = *a.begin();
            a.erase(a.begin());
            // второй минимум:
            auto min2 = *a.begin();
            a.erase(a.begin());
            // вставляем их сумму минус 1:
            a.insert(min1 + min2 - 1);
        }
        // выводим ответ
        std::cout << *a.rbegin() << "\n";
    }
}
