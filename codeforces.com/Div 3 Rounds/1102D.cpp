/*
    problem: 1102D. Balanced Ternary String
    solution: strings, greedy
*/
#include "template.hpp"
std::string v2s(vi v) {
    std::string s(isz(v), '0');
    for (int i = 0; i < isz(v); i++)
        s[i] = char(v[i] + '0');
    return s;
}
std::string solve(vi s) {
    const int need = isz(s) / 3;
    int cnt[3]{};
    for (auto it : s)
        cnt[it]++;
    // first round: replace by less values from left to right:
    for (int i = 0; i < isz(s); i++) {
        if (cnt[s[i]] > need) {
            int replaceBy = -1;
            for (int to = 0; to < 3; to++)
                if (cnt[to] < need) {
                    replaceBy = to;
                    break;
                }
            if (replaceBy >= s[i]) {
                // ignore
            } else {
                cnt[s[i]]--;
                s[i] = replaceBy;
                cnt[replaceBy]++;
            }
        }
    }
    // second round: replace by greater values from right to left:
    for (int i = isz(s)-1; i >= 0; i--) {
        if (cnt[s[i]] > need) {
            int replaceBy = -1;
            for (int to = 2; to >= 0; to--)
                if (cnt[to] < need) {
                    replaceBy = to;
                    break;
                }
            if (replaceBy < s[i]) {
                // ignore
            } else {
                cnt[s[i]]--;
                s[i] = replaceBy;
                cnt[replaceBy]++;
            }
        }
    }
    assert(cnt[0] == need && cnt[1] == need && cnt[2] == need);
    return v2s(s);
}
vi s2v(std::string s) {
    vi v(isz(s));
    for (int i = 0; i < isz(s); i++)
        v[i] = s[i] - '0';
    return v;
}
std::string solve(std::string s) {
    return solve(s2v(s));
}
int main() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;
    std::cout << solve(s) << std::endl;
}
