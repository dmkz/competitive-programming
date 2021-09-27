// Решение: математическое ожидание, O(t)
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129987159
#include <bits/stdc++.h>
int main() {
    std::cout << std::fixed << std::setprecision(9);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int64_t n; std::cin >> n;
        double p0,p1,p2,p3;
        std::cin >> p0 >> p1 >> p2 >> p3;
        // по свойствам матожидания, M(бросок1 + ... + бросокN) = M(бросок1)+...+M(бросокN)
        // Все броски одинаковые, поэтому M(бросок * n) = n * M(бросок)
        // Формула для M для одного броска дана в условии. Подставляя, получаем ответ:
        std::cout << (p1+2*p2+3*p3)*n << std::endl;
    }
}