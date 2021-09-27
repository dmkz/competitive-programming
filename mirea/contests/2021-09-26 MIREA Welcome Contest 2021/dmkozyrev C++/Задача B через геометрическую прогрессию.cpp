// Решение: математика, геометрическая прогрессия, O(q*log(t))
// Ссылка: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129986428
#include <bits/stdc++.h>
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // это прогрессия вида a, a*b, a*b^2, a*b^3, ..., a*b^t
        // для поиска b делим заданный a*b^6 на a*b^3 и извлекаем кубический корень:
        int coeff = cbrt(352947/1029);
        // для находления a делим заданный a*b^3 на b^3:
        int start = 1029 / pow(coeff,3);
        int t; std::cin >> t;
        // выводим ответ:
        int result = start * pow(coeff,t);
        std::cout << result << std::endl;
    }
}