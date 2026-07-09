// строки, подсчёт символов, перебор, подмножества
// Задача: C, Вердикт: OK, Время: 0.013 сек, Память: 2.6 МБ
#include <bits/stdc++.h>
#include <cassert>
const std::vector<std::string> courses = {"MWS Octapi", "MWS Data", "MWS Tables",
                                          "MWS AI", "MWS Cloud Platform"};
using Count = std::valarray<int>;
Count getCount(const std::string &s) {
    Count res(0, 52);
    for (auto it : s) {
        if (std::isspace(it))
            continue;
        if ('A' <= it && it <= 'Z')
            res[26 + (it - 'A')] += 1;
        else
            res[(it - 'a')] += 1;
    }
    return res;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int bestScore1 = 0, bestCount1 = 1;
        int bestScore2 = 0, bestSwaps2 = 0;
        std::string s; std::cin >> s;
        auto have = getCount(s);
        for (int subset = 1; subset < (1 << 5); subset++) {
            // можем ли получить текущее подмножество?
            // сколькими способами?
            Count want(0, 52);
            int cnt{};
            for (int i = 0; i < 5; i++)
                if ((subset >> i) & 1) {
                    want += getCount(courses[i]);
                    cnt++;
                }
            bool ok1 = true;
            for (int i = 0; i < 52; i++)
                ok1 &= (want[i] <= have[i]);
            if (ok1) {
                if (bestScore1 < cnt) {
                    bestScore1 = cnt;
                    bestCount1 = 1;
                } else if (bestScore1 <= cnt) {
                    bestCount1++;
                }
            }
            bool ok2 = true;
            int numSwaps{};
            for (int i = 0; i < 26; i++) {
                if (have[i] + have[i + 26] >= want[i] + want[i + 26]) {
                    numSwaps += std::max(0, want[i] - have[i]);
                    numSwaps += std::max(0, want[i + 26] - have[i + 26]);
                } else {
                    ok2 = false;
                }
            }
            if (ok2) {
                if (bestScore2 < cnt) {
                    bestScore2 = cnt;
                    bestSwaps2 = numSwaps;
                } else if (bestScore2 == cnt) {
                    if (bestSwaps2 > numSwaps)
                        bestSwaps2 = numSwaps;
                }
            }
        }
        std::cout << bestScore1 << ' ' << bestCount1 << ' '
                  << bestScore2 << ' ' << bestSwaps2 << '\n';
    }
}
