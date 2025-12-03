#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void solveEasy() {
    std::string s;
    int sum{};
    while (std::getline(std::cin, s)) {
        int answ = 0;
        int max = s.back() - '0';
        for (int i = isz(s)-2; i >= 0; i--) {
            int curr = s[i] - '0';
            answ = std::max(answ, curr * 10 + max);
            max = std::max(max, curr);
        }
        sum += answ;
    }
    std::cout << sum << std::endl;
}
using ll = long long;
const ll inf = (ll)1e18L;
void solveHard() {
    std::vector<ll> pow10(13, 1);
    for (int i = 1; i < 13; i++)
        pow10[i] = 10 * pow10[i-1];
    std::string s;
    ll sum{};
    while (std::getline(std::cin, s)) {
        std::map<std::pair<int, int>, ll> cache;
        std::function<ll(int,int)> solve = [&](int pos, int nDigits) -> ll
        {
            if (nDigits == 0)
                return 0;
            if (pos == isz(s))
                return -inf;
            auto key = std::make_pair(pos, nDigits);
            if (auto it = cache.find(key); it != cache.end())
                return it->second;
            ll answ1 = 0, answ2 = 0;
            answ1 = solve(pos+1, nDigits);
            answ2 = solve(pos+1, nDigits-1) + pow10[nDigits-1] * (s[pos] - '0');
            return cache[key] = std::max(answ1, answ2);
        };
        ll curr = solve(0, 12);
        //std::cout << "s = '" << s << "' --> " << curr << std::endl;
        sum += curr;
    }
    std::cout << sum << std::endl;
}
void solveHard2() {
    std::vector<ll> pow10(13, 1);
    for (int i = 1; i < 13; i++)
        pow10[i] = 10 * pow10[i-1];
    std::string s;
    ll sum{};
    while (std::getline(std::cin, s)) {
        // инициализация:
        std::vector dp(isz(s)+1, std::vector<ll>(13, -inf));
        for (int pos = isz(s); pos >= 0; pos--)
            dp[pos][0] = 0;
        // переходы:
        for (int pos = isz(s)-1; pos >= 0; pos--)
            for (int nDigits = 1; nDigits <= 12; nDigits++) {
                ll answ1 = dp[pos+1][nDigits];
                ll answ2 = dp[pos+1][nDigits-1] + pow10[nDigits-1] * (s[pos] - '0');
                dp[pos][nDigits] = std::max(answ1, answ2);
            }
        ll curr = dp[0][12];
        //std::cout << "s = '" << s << "' --> " << curr << std::endl;
        sum += curr;
    }
    std::cout << sum << std::endl;
}
main() {
    solveHard2();
}
