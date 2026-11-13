#include <bits/stdc++.h>
#include <bits/extc++.h>
#define all(x) (x).begin(),(x).end()
#define int int64_t
const int inf = 1e18L;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
int32_t main() {
    int n, len, a; std::cin >> n >> len >> a;
    std::vector items(n, std::vector<std::tuple<int,int,int>>{}); // {width, height, cost}
    for (int i = 0; i < n; i++) {
        int w, h, a0, a1, a2, a3;
        std::cin >> w >> h >> a0 >> a1 >> a2 >> a3;
        items[i].emplace_back(w, h, std::max(a0, a2));
        items[i].emplace_back(h, w, std::max(a1, a3));
    }
    // sum W <= len
    // max H <= answ
    // sum cost >= a
    auto check = [&](int maxH){
        // можно ли, взяв только картины высотой <= maxH, добиться суммарной стоимости >= a,
        // используя длину l? dp[l] = max total cost
        std::vector<int> curr(1+len, -inf);
        curr[0] = 0;
        for (int i = 0; i < n; i++) {
            auto next = curr;
            const auto &[w1, h1, a1] = items[i][0];
            const auto &[w2, h2, a2] = items[i][1];
            if (h1 <= maxH)
                for (int was = len-w1; was >= 0; was--)
                    setmax(next[was+w1], curr[was] + a1);
            if (h2 <= maxH)
                for (int was = len-w2; was >= 0; was--)
                    setmax(next[was+w2], curr[was] + a2);
            curr.swap(next);
        }
        return *std::max_element(all(curr)) >= a;
    };
    // бинарный поиск по ответу - максимальной высоте картины
    int low = -1, high = 1e5;
    while (high - low > 1) {
        int mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    if (high >= 1e4) std::cout << "-1\n";
    else std::cout << high << "\n";
    return 0;
}