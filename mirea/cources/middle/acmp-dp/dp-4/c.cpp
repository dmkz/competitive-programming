#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9+9;
int main() {
    // решето Эратосфена:
    vector<bool> isPrime(1001, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < 1001; i++)
        if (isPrime[i])
            for (int j = i * i; j < 1001; j+=i)
                isPrime[j] = false;
    // инициализация динамики:
    // dp[число разрядов][две последние взятые цифры] => количество чисел
    int n; cin >> n;
    vector<vector<int>> dp(n+1, vector<int>(101, 0));
    for (int x = 100; x <= 999; x++)
        dp[3][x%100] += isPrime[x];
    // переходы:
    for (int i = 4; i <= n; i++)
        for (int number = 100; number <= 999; number++)
            if (isPrime[number]) {
                dp[i][number%100] += dp[i-1][number/10];
                dp[i][number%100] %= mod;
            }
    // ответ:
    int64_t answ = 0;
    for (int x = 0; x <= 99; x++)
        answ += dp[n][x];
    cout << answ % mod << endl;
}