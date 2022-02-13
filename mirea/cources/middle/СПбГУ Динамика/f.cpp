#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
using vi = vector<int>;
using vvi = vector<vi>;
void setmin(auto &x, auto y) { if (y < x) x = y; }
int main() {
    //freopen("balls.in", "rt", stdin);
    //freopen("balls.out", "wt", stdout);
    const int MAX = 300300;
    // предподсчитаем количество шаров во всех валидных пирамидках:
    vector<int> piramidas;
    for (int n = 1, sum = 0; sum <= MAX; n++) {
        sum += n * (n+1)/2;
        piramidas.push_back(sum);
    }
    // считаем динамику: dp[n] - минимальное число пирамидок из n шаров
    vector<int> dp(1+MAX,INF);
    dp[0] = 0;
    for (int n = 1; n <= MAX; n++)
        // всего n шаров
        // перебираем сколько шаров было в последней пирамиде
        for (int last : piramidas)
            if (n-last >= 0)
                setmin(dp[n],dp[n-last]+1);
    int tt; cin >> tt;
    while (tt --> 0) {
        int m; cin >> m;
        cout << dp[m] << '\n';
    }
}