/*
    Задача: 918. График
    
    Решение: жадный алгоритм, динамическое программирование, двумерное дп, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define remax(x, y) (x) = (x) < (y) ? (y) : (x)
struct Order { int last, cost; };
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<Order> orders(n);
        for (auto & it : orders) { std::cin >> it.last >> it.cost; }
        std::sort(all(orders), [&](const Order& a, const Order& b) {
            return a.last < b.last || (a.last == b.last && a.cost > b.cost);
        });
        // dp[seen][taken]
        std::vector<std::vector<int>> dp(1+n, std::vector<int>(1+n));
        for (int i = 0; i < n; ++i) {
            for (int take = 0; take <= i; ++take) {
                if (take+1 <= orders[i].last) {
                    remax(dp[i+1][take+1], dp[i][take] + orders[i].cost);
                }
                remax(dp[i+1][take], dp[i][take]);
            }
        }
        std::cout << *std::max_element(all(dp[n])) << std::endl;
    }
    return 0;
}