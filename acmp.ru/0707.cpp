// динамическое программирование по подмножествам, O(2^n * n^2)
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using pic = std::pair<int, char>;
using vi = std::vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }
main() {
    // читаем данные
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::string s; std::cin >> s;
    // dp[mask] <-- какие шары остались и за сколько их можно уничтожить
    const int n = isz(s);
    std::vector dp(1 << n, std::make_pair(11, std::vector<pic>(11)));
    dp[0] = std::make_pair(0, std::vector<pic>(0));
    for (int mask = 1; mask < isz(dp); mask++) {
        // сформируем строку, которая стоит перед нами прямо сейчас
        std::string curr;
        vi pos;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) {
                curr += s[i];
                pos.push_back(i);
            }
        // теперь переберём все выстрелы в блоки:
        for (int i = 0, j; i < isz(curr); i = j) {
            for (j = i; j < isz(curr) && curr[i] == curr[j]; j++);
            // сколько раз нужно стрельнуть, чтобы схлопнуть
            // отрезок [i, j)
            int len = j - i;
            int cnt = std::max(1, 3 - len);
            // делаем выстрел и считаем как это всё схлопнется
            int f = i-1, s = j;
            while (true) {
                if (f >= 0 && s < isz(curr) && curr[f] == curr[s]) {
                    int cntLeft = 1;
                    while (f-1 >= 0 && curr[f-1] == curr[s]) {
                        f--;
                        cntLeft++;
                    }
                    int cntRight = 1;
                    while (s+1 < isz(curr) && curr[s+1] == curr[f]) {
                        s++;
                        cntRight++;
                    }
                    if (cntLeft + cntRight < 3) {
                        break;
                    } else {
                        s++, f--;
                    }
                } else break;
            }
            int prevMask = 0;
            for (int i = 0; i <= f; i++)
                prevMask |= (1 << pos[i]);
            for (int i = s; i < isz(curr); i++)
                prevMask |= (1 << pos[i]);
            auto prevVector = dp[prevMask].second;
            while (cnt --> 0)
                prevVector.emplace_back(pos[i], curr[i]);
            remin(dp[mask], std::make_pair(isz(prevVector), prevVector));
        }
    }
    auto [answ, vec] = dp[(1<<n)-1];
    std::cout << answ;
    std::reverse(all(vec));
    for (const auto &[p, c] : vec)
        std::cout << ' ' << c << p;
    std::cout << std::endl;
}
