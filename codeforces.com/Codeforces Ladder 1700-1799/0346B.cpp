/*
    Problem: 346B. Lucky Common Subsequence
    
    Solution: dynamic programming, strings, O(|s|*|t|*|v|+26*|v|^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int NMAX = 110, INF = (int)1e9+7;
struct State {
    int cnt, slen, tlen, vlen;
    char c;
    State(int cnt_ = 0, int is_ = 0, int it_ = 0, int iv_ = 0, char c_ = '\0')
        : cnt(cnt_), slen(is_), tlen(it_), vlen(iv_), c(c_) { }
};
bool operator<(const State& a, const State& b) {
    if (a.cnt < b.cnt) { return true; }
    if (a.cnt > b.cnt) { return false; }
    if (a.slen < b.slen) { return true; }
    if (a.slen > b.slen) { return false; }
    if (a.tlen < b.tlen) { return true; }
    if (a.tlen > b.tlen) { return false; }
    if (a.vlen < b.vlen) { return true; }
    if (a.vlen > b.vlen) { return false; }
    return a.c < b.c;
}
template<typename T> bool operator>(const T& a, const T& b) { return b < a; }
template<typename X, typename Y> X& remax(X& x, Y y) { return x = (x > y) ? x : y; }
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (std::string s, t, v; std::cin >> s >> t >> v; ) {
        // to[len][char] -> newLen
        vvi to(isz(v)+1,vi(26,0));
        for (int have = 0; have <= isz(v); ++have) {
            auto ss = v.substr(0,have);
            for (char c = 'A'; c <= 'Z'; c++) {
                ss.push_back(c);
                int mx = 0;
                for (int len = 1; len <= isz(ss) && len <= isz(v); ++len) {
                    if (ss.substr(isz(ss)-len,len) == v.substr(0,len)) {
                        mx = len;
                    }
                }
                to[have][c-'A'] = mx;
                ss.pop_back();
            }
        }
        static State dp[NMAX][NMAX][NMAX];
        std::fill(&dp[0][0][0],&dp[0][0][0]+NMAX*NMAX*NMAX,State(-INF));
        dp[0][0][0] = State();
        for (int slen = 0; slen <= isz(s); ++slen) {
            for (int tlen = 0; tlen <= isz(t); ++tlen) {
                for (int vlen = 0; vlen <= isz(v); ++vlen) {
                    if (tlen > 0) {
                        dp[slen][tlen][vlen] = dp[slen][tlen-1][vlen];
                    }
                    if (slen > 0) {
                        remax(dp[slen][tlen][vlen], dp[slen-1][tlen][vlen]);
                    }
                }
                if (slen > 0 && tlen > 0 && s[slen-1] == t[tlen-1]) {
                    char curr = s[slen-1];
                    for (int vlen = 0; vlen < isz(v); ++vlen) {
                        int next = to[vlen][curr-'A'];
                        if (next == isz(v)) { continue; }
                        auto prev = dp[slen-1][tlen-1][vlen].cnt;
                        remax(dp[slen][tlen][next], State(prev+1,slen-1,tlen-1,vlen,curr));
                    }
                }
            }
        }
        State st;
        for (int vlen = 0; vlen < isz(v); vlen++) {
            st = std::max(st, dp[isz(s)][isz(t)][vlen]);
        }
        std::string answ(st.cnt, '?');
        for (int cnt = st.cnt; cnt > 0; --cnt) {
            answ[cnt-1] = st.c;
            st = dp[st.slen][st.tlen][st.vlen];
        }
        if (isz(answ) == 0) { std::cout << 0 << std::endl; }
        else { std::cout << answ << std::endl; }
    }
    return 0;
}