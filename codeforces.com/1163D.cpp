/*
    Problem: 1163D. Mysterious Code
    
    Solution: dynamic programming, strings, O(|c|*|s|*|t|*26)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
template<typename T> T& remax(T& x, T y) { return x = (y > x) ? y : x; }
const int INF = (int)1e9+7;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (std::string c, s, t; std::cin >> c >> s >> t; ) {
        // Init dp table:
        static int dp[51][51][1001];
        std::fill(&dp[0][0][0], &dp[0][0][0]+51*51*1001, -INF);
        dp[0][0][0] = 0;
        // Init rules:
        struct State { int ns, nt; char c; };
        std::vector<State> rules[51][51];
        std::fill(&rules[0][0], &rules[0][0]+51*51, std::vector<State>());
        for (int ns = 0; ns <= isz(s); ++ns) {
            for (int nt = 0; nt <= isz(t); ++nt) {
                for (char curr = 'a'; curr <= 'z'; ++curr) {
                    auto ss = s.substr(0,ns) + std::string(1, curr);
                    auto tt = t.substr(0,nt) + std::string(1, curr);
                    int ms = 0;
                    for (int is = 0; is <= isz(s) && is <= isz(ss); ++is) {
                        if (ss.substr(isz(ss)-is,is) == s.substr(0,is)) {
                            ms = is;
                        }
                    }
                    int mt = 0;
                    for (int it = 0; it <= isz(t) && it <= isz(tt); ++it) {
                        if (tt.substr(isz(tt)-it,it) == t.substr(0,it)) {
                            mt = it;
                        }
                    }
                    rules[ns][nt].push_back(State{ms,mt,curr});
                }
            }
        }
        // Fill dp table:
        for (int len = 1; len <= isz(c); ++len) {
            const char curr = c[len-1];
            for (int ns = 0; ns <= isz(s); ++ns) {
                for (int nt = 0; nt <= isz(t); ++nt) {
                    #define update(x,y,u,v) remax(dp[(x)][(y)][len], dp[(u)][(v)][len-1] + int((x) == isz(s)) - int((y) == isz(t)))
                    for (const auto& rule : rules[ns][nt]) {
                        if (curr == '*' || curr == rule.c) {
                            update(rule.ns,rule.nt,ns,nt);
                        }
                    }
                }
            }
        }
        int answ = -INF;
        for (int ns = 0; ns <= isz(s); ++ns) {
            for (int nt = 0; nt <= isz(t); ++nt) {
                remax(answ, dp[ns][nt][isz(c)]);
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}