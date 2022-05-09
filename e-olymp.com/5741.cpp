/*
    Задача: 5741. Стек шаров
    Решение: динамическое программирование, поворот на 45 градусов, O(n^2)
*/
#include <bits/stdc++.h>
void setmax(auto &x, const auto &y) {
    if (x < y) x = y;
}
using ll = long long;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
const ll INF = (ll)1e18L;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while (std::cin >> n,n) {
        // читаем треугольник, располагая его на диагоналях
        // в половинке квадрата (поворот на 45 градусов)
        vvl a(n,vl(n));
        for (int diag = 0; diag < n; diag++) {
            for (int i = diag; i >= 0; i--) {
                std::cin >> a[i][diag-i];
            }
        }
        // префикс-суммы внутри каждой строки:
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i][j] += (j-1>=0?a[i][j-1]:0);
        // динамика - надо выбрать последовательность из префикс-сумм так,
        // чтобы в каждой строке была выбрана ровно одна префикс-сумма и
        // и для каждого выбранного элемента (row1,col1) те элементы, которые
        // расположены ниже его (row2 >= row1), должны лежать левее егоб т.е.
        // (col2 <= col1). Среди всех вариантов нужно выбрать последовательность
        // с максимальной суммой. Вывести эту сумму        
        vvl dp(n+1,vl(n,-INF));
        for (int row = n-1; row >= 0; row--) {
            ll maxInPrevRow = 0;
            for (int col = 0; col < n; col++) {
                setmax(maxInPrevRow, dp[row+1][col]);
                setmax(dp[row][col], a[row][col] + maxInPrevRow);
            }
        }
        // выводим ответ:
        ll answ = 0;
        for (int col = 0; col < n; col++)
            setmax(answ, dp[0][col]);
        std::cout << answ << '\n';
    }
}