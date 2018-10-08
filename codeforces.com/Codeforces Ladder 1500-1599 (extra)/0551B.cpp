/*
    Problem: 551B. ZgukistringZ
    
    Solution: strings, implementation, O(26*n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

const int INF = (int)1e9+7;

#define size(x) (int)(x).size()

typedef std::vector<int> vi;

vi get_cnt(const std::string& s) {
    vi answ(26); for (auto it : s) answ[it-'a']++;
    return answ;
}

int solve(const int n2, const vi& cnt1, const vi& cnt2, const vi& cnt3) {
    int mx = n2;
    for (int i = 0; i < 26; ++i) {
        if (cnt2[i] == 0) continue;
        mx = std::min(mx, cnt1[i] / cnt2[i]);
    }
    if (mx < n2) return -INF;
    vi rem(26);
    mx = INF;
    for (int i = 0; i < 26; ++i) {
        rem[i] = cnt1[i] - n2 * cnt2[i];
        if (cnt3[i] != 0) {
            mx = std::min(mx, rem[i] / cnt3[i]);
        }
    }
    return mx;
}

int main() {
    std::string a, b, c; 
    std::cin >> a >> b >> c;
    vi cnt1 = get_cnt(a);
    vi cnt2 = get_cnt(b);
    vi cnt3 = get_cnt(c);
    int mx2 = 0, mx3 = 0;
    for (int n2 = 0; n2 <= size(a) / size(b); ++n2) {
        int n3 = solve(n2, cnt1, cnt2, cnt3);
        if (mx2 + mx3 < n2 + n3) {
            mx2 = n2;
            mx3 = n3;
        }
    }
    a = "";
    for (int i = 0; i < mx2; ++i) a += b;
    for (int i = 0; i < mx3; ++i) a += c;
    for (int i = 0; i < 26; ++i) {
        cnt1[i] -= mx2 * cnt2[i] + mx3 * cnt3[i];
        a += std::string(cnt1[i], 'a' + i);
    }
    std::cout << a;
    return 0;
}