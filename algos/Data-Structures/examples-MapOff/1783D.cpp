#pragma GCC optimize("Ofast")
#include "template.hpp"
#include "debug.hpp"
#include "mapoff.hpp"
const int mod = 998244353;
int main() {
    int n; std::cin >> n;
    vi a(n); std::cin >> a;
    std::vector<MapOff<int,int>> dp(n);
    dp[1].add_key(a[1]);
    dp[1].build();
    dp[1][a[1]] = 1;
    for (int i = 1; i != n - 1; i++) {
        // добавляем ключи на следующем уровне:
        for (const auto &[key, _] : dp[i]) {
            if (key == 0) dp[i+1].add_key(a[i+1]);
            else dp[i+1].add_key(a[i+1] + key, a[i+1] - key);
        }
        dp[i+1].build();
        // обновляем динамику на следующем уровне:
        auto eq = dp[i+1].begin();
        auto plus = dp[i+1].begin();
        auto minus = dp[i+1].rbegin();
        for (const auto &[key,value] : dp[i]) {
            if (key == 0) {
                while (eq->first != a[i+1]) eq++;
                (eq->second += value) %= mod;
            }
            else {
                while (plus->first != (a[i+1]+key)) plus++;
                (plus->second += value) %= mod;
                while (minus->first != (a[i+1]-key)) minus++;
                (minus->second += value) %= mod;
            }
        }
    }
    int64_t answ{};
    for (const auto &[_,val] : dp.back()) answ += val;
    std::cout << answ % mod << std::endl;
}
