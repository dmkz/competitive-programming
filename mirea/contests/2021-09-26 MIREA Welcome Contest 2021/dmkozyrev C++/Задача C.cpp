// Решение: математика, O(t)
// Ссылка на сабмит: https://codeforces.com/group/LB1sSRhotq/contest/346286/submission/129986620
#include <bits/stdc++.h>
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int64_t n,L,R; std::cin >> n >> L >> R;
        // нужно посчитать, сколько чисел на полуинтервале [L,R) делятся на n
        // пусть это f(L,R). Тогда f(L,R) = f(0,R) - f(0,L)
        // f(0,R) вычисляется как (R-1)/n
        // аналогично f(0,L) = (L-1)/n
        std::cout << (R-1)/n-(L-1)/n << std::endl;
    }
}