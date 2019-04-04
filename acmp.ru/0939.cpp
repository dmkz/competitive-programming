/*
    Задача: 939. Золотоискатели
    
    Решение: динамическое программирование, двумерное дп, O(n^2*w)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
typedef std::pair<int,int> pii;
typedef std::vector<pii> vpii;
typedef std::vector<vpii> vvpii;
typedef std::vector<int> vi;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vi w(n);
        for (auto &it : w) { std::cin >> it; }
        const int max = *std::max_element(all(w)) * n;
        const int sum = std::accumulate(all(w),0);
        if (sum / 3 * 3 != sum) {
            std::cout << 0 << std::endl; 
            continue;
        }
        vvpii dp(1+n, vpii(1+max,pii(-1,-1)));
        dp[0][0] = pii(0,-1);
        for (int i = 1; i <= n; ++i) {
            const int t = w[i-1];
            for (int s = t; s <= max; ++s) {
                if (dp[i-1][s-t].first == -1) { continue; }
                dp[i][s] = pii(i-1, i-1);
            }
            for (int s = 0; s <= max; ++s) {
                if (dp[i][s].first == -1) {
                    dp[i][s] = dp[i-1][s];
                }
            }
        }
        int s = sum / 3;
        if (dp[n][s].first == -1) {
            std::cout << 0 << std::endl;
            continue;
        }
        pii last = dp[n][s];
        vi answ;
        while (last.second != -1) {
            answ.push_back(last.second+1);
            const int wt = w[last.second];
            s -= wt;
            assert(s >= 0);
            last = dp[last.first][s];
        }
        assert(s == 0);
        std::cout << answ.size() << "\n";
        for (auto it : answ) { std::cout << it << ' '; }
        std::cout << std::endl;
    }
    return 0;
}