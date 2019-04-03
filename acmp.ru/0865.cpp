/*
    Задача: 865. Проверка орфографии
    
    Решение: строки, динамическое программирование, O(n*len(text)*len(word))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
typedef std::vector<std::string> vs;
int f(char c1, char c2) {
    c1 = std::tolower(c1);
    c2 = std::tolower(c2);
    if (c1 > c2) { std::swap(c1,c2); }
    return std::min(c2-c1,c1+26-c2);
}
int f(const std::string& fi, const std::string& se) {
    assert(isz(fi) == isz(se));
    int res = 0;
    for (int i = 0; i < isz(fi); ++i) {
        res += f(fi[i], se[i]);
    }
    return res;
}
const int INF = (int)1e9+7;
struct Record {
    int val; std::string* what;
};
bool operator<(const Record& a, const Record& b) {
    return a.val < b.val || (a.val == b.val && a.what < b.what);
}
std::string NULL_STR = "";
std::string solve(std::string s, vs& w) {
    s = "?" + s;
    std::vector<Record> dp(isz(s), Record{INF, &NULL_STR});
    dp[0].val = 0;
    for (int last = 1; last < isz(s); ++last) {
        for (std::string& what : w) {
            if (isz(what) <= last) {
                int res = dp[last-isz(what)].val;
                res += f(s.substr(last-isz(what)+1,isz(what)), what);
                res = std::min(res, INF);
                dp[last] = std::min(dp[last], Record{res, &what});
            }
        }
    }
    int res = dp.back().val;
    std::string ret;
    if (res == INF) {
        ret = "-1";
        return ret;
    }
    std::vector<std::string> answ;
    for (int last = isz(s)-1; last > 0; ) {
        answ.push_back(*dp[last].what);
        last -= isz(*dp[last].what);
    }
    std::reverse(all(answ));
    for (auto &it : answ) { ret += it; }
    s.erase(0,1);
    for (int i = 0; i < isz(ret); ++i) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            ret[i] = std::toupper(ret[i]);
        } else if ('a' <= s[i] && s[i] <= 'z') {
            ret[i] = std::tolower(ret[i]);
        }
    }
    assert(res == f(ret,s));
    return ret;
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        vs w(n);
        for (auto &it : w) std::cin >> it;
        std::string s; std::cin >> s;
        std::cout << solve(s, w) << std::endl;
    }
    return 0;
}