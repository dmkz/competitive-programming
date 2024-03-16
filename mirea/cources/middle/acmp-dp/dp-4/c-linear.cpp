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
    vector<int> curr_dp(101, 0);
    for (int x = 100; x <= 999; x++)
        curr_dp[x % 100] += isPrime[x];
    // переходы:
    for (int i = 4; i <= n; i++) {
        // копирование
        auto prev_dp = curr_dp;
        // заполнение нулями
        fill(curr_dp.begin(), curr_dp.end(), 0);
        // переходы
        for (int number = 100; number <= 999; number++) {
            if (isPrime[number]) {
                curr_dp[number%100] += prev_dp[number/10];
                curr_dp[number%100] %= mod;
            }
        }
    }
    // ответ:
    int64_t answ = 0;
    for (int x = 0; x <= 99; x++)
        answ += curr_dp[x];
    cout << answ % mod << endl;
}
