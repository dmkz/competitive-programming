#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    // dp[k][p] = число способов представить число k в виде суммы степеней двоек при
    // условии, что максимальная степень двойки в разложении равна p
    vector dp(1+n, vector(10, 0));
    // инициализация динамики:
    // нулевое число:
    dp[0][0] = 1;
    // переходы динамики
    for (int k = 1; k <= n; k++)
        for (int p = 0; p < 10 && (1 << p) <= k; p++)
            // добавляем 2^p в разложение
            for (int prevPower = 0; prevPower <= p; prevPower++)
                dp[k][p] += dp[k - (1 << p)][prevPower];
    // считаем ответ:
    cout << accumulate(all(dp[n]), 0) << endl;
}
