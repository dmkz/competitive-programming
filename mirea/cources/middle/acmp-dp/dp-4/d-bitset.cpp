#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
int main() {
    int n, m; cin >> n >> m;
    if (n < m)
        swap(n, m);
    // надо хранить вариант заполнения последней строки,
    // это один из 2^m комбинаций
    // dp[строка][способ заполнения последней строки] => кол-во вариантов
    vector dp(n, vector(1 << m, 0));
    // заполняем единицами все варианты для первой строки
    dp[0] = vector(1 << m, 1);
    // осуществяем переходы
    for (int row = 1; row < n; row++)
        for (int currRow = 0; currRow < (1 << m); currRow++)
            for (int prevRow = 0; prevRow < (1 << m); prevRow++) {
                bitset<30> prev(prevRow);
                bitset<30> curr(currRow);
                bool ok = true;
                for (int col = 0; col + 1 < m; col++) {
                    // проверяем элементы в квадрате 2х2, что они не равны
                    // одному и тому же числу x
                    const int x = prev[col];
                    if (x == curr[col] && x == curr[col+1] && x == prev[col+1])
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    dp[row][currRow] += dp[row-1][prevRow];
                }
            }
    cout << accumulate(all(dp[n-1]), 0LL) << endl;
}
