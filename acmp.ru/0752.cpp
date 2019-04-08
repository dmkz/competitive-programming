/*
    Задача: 752. 2-3 Дерево
    
    Решение: динамическое программирование, двумерное дп, комбинаторика, O(log(n)*n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>

typedef unsigned long long ull;

int solve(const int need, const int mod) {
    if (need == 1) { return 1 % mod; }
    if (mod == 1) { return 0; }
    std::vector<std::vector<ull>> dp(14, std::vector<ull>(1024 * 8, 0)); // [depth][nLeafs] -> count
    dp[1][2] = dp[1][3] = 1;
    for (int depth = 2; depth < 14; ++depth) {
        // 2 branches
        for (int sum = 0; sum <= need; ++sum) {
            for (int cnt = 0; cnt <= sum; ++cnt) {
                dp[depth][sum] += dp[depth-1][cnt] * dp[depth-1][sum - cnt];
                if (cnt % 16 == 0) {
                    dp[depth][sum] %= mod;
                }
            }
        }
        // 3 branches
        for (int sum = need; sum >= 0; --sum) {
            for (int cnt = sum; cnt >= 0; --cnt) {
                dp[depth][sum] += dp[depth][cnt] * dp[depth-1][sum - cnt];
                if (cnt % 16 == 0) {
                    dp[depth][sum] %= mod;
                }
            }
        }
    }
    ull answ = 0;
    for (int depth = 1; depth < 14; ++depth) {
        answ += dp[depth][need];
    }
    return int(answ % mod);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    for (int n, mod; std::cin >> n >> mod; std::cout << solve(n, mod) << std::endl);
    return 0;
}