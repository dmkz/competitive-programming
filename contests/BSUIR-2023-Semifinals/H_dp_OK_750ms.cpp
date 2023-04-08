#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("fma")
#include <bits/stdc++.h>
const int mod = (int)1e9+7;
// ответы для проверки:
// 500 500: 904795293
// 20000 20000: 987353482
int main() { 
    int n, m; std::cin >> n >> m;
    if (n > m) std::swap(n,m);
    // делаем номер строки <= номера столбца для симметрии, то есть
    // будем хранить только верхний треугольник динамики
    // нужно знать четыре слоя динамики, так как за один ход сумма координат
    // увеличивается либо на 1, либо на 3
    // соответственно динамику для каждой точки последних 4-х диагоналей храним
    const int zero = (n+m)*2;
    std::vector storage(4, std::vector(2*zero+1, 0));
    std::vector<int*> dp(4);
    for (int i = 0; i < 4; i++)
        dp[i] = &storage[i][zero];
    // теперь мы можем использовать отрицательные индексы в dp
    // чтобы сэкономить, нам нужно для каждой диагонали знать
    // достижимые клетки от (0,0) и от (n,m), то есть перебирать только их
    // считаем достижимые из (0,0):
    std::vector<int> min1(n+m+1), max1(n+m+1); // min и max достижимые строки
    min1[0] = max1[0] = 0;
    for (int diag = 1; diag <= n + m; diag++) {
        min1[diag] = min1[diag-1]-1;
        max1[diag] = max1[diag-1]+2;
    }
    // считаем достижимые из (n,m):
    std::vector<int> min2(n+m+1), max2(n+m+1); // min и max достижимые строки
    min2[n+m] = max2[n+m] = n;
    for (int diag = n+m-1; diag >= 0; diag--) {
        min2[diag] = min2[diag+1]-2;
        max2[diag] = max2[diag+1]+1;
    }
    // считаем саму динамику:
    dp[0][0] = 1;
    for (int diag = 1; diag <= n + m; diag++)
    {
        // границы перебора на текущей диагонали:
        const int min = std::max(min1[diag],min2[diag]);
        const int max = std::min({max1[diag],max2[diag],diag/2});
        // текущая диагональ:
        int * __restrict diag0 = dp[diag%4];
        // предыдущая диагональ на расстоянии 1:
        const int * __restrict diag1 = dp[(diag-1+4)%4];
        // предыдущая диагональ на расстоянии 3:
        const int * __restrict diag3 = dp[(diag-3+4)%4];
        int row;
        for (row = min; row <= max-3; row++) {
            uint32_t x  = diag1[row-2];
                     x += diag3[row-2];
                     x += diag3[row-1];
                     x += diag1[row+1];
            diag0[row] = x % mod;
        }
        // последние три элемента обрабатываем аккуратно,
        // чтобы не вылезить за главную диагональ, т.е. за хранимую
        // область симметрии
        for(;row <= max; row++) {
            const int col = diag - row;
            uint32_t x  = diag1[row-2];
                     x += diag3[row-2];
                     x += diag3[std::min(row-1,col-2)];
                     x += diag1[std::min(row+1,col-2)];
            diag0[row] = x % mod;
        }
    }
    std::cout << dp[(n+m)%4][n] << '\n';
}
