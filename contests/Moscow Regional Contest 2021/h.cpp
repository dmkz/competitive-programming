#include <bits/stdc++.h>
// useful stuff:
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
void setmin(auto &x, auto y) { if (y < x) x = y; }
const int INF = (int)1e9;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
// list of all roman palindromes:
const std::vector<std::string> pal = {
    "I",
    "II",
    "III",
    "V",
    "X",
    "XIX",
    "XX",
    "XXX",
    "L",
    "C",
    "CXC",
    "CC",
    "CCC",
    "D",
    "M",
    "MCM",
    "MM",
    "MMM"};
int main() {
    // input:
    int n; std::string s;
    std::cin >> n >> s;
    s = "$" + s;
    // calculate dp:
    vpii dp(1+n, pii(INF,INF));
    dp[0]={0,0};
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < isz(pal); j++) {
            auto t = pal[j];
            if (i - isz(t) >= 0 && s.substr(i-isz(t)+1,isz(t)) == t) {
                setmin(dp[i],pii{dp[i-isz(t)].first+1,j});
            }
        }
    }
    // get answer:
    std::vector<std::string> answ;
    int last = n;
    while (last > 0) {
        auto [_,j] = dp[last];
        answ.push_back(pal[j]);
        last -= isz(pal[j]);
    }
    std::reverse(all(answ));
    // print answer:
    std::cout << isz(answ) << '\n';
    for (auto &it : answ) std::cout << it << '\n';
    return 0;
}