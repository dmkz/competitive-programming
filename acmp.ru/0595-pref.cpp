#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

std::vector<int> prefix(const std::string& s) {
// Нахождение префикс-функции от строки за линейное время
    const int n = s.size();
    int len = 0;
    std::vector<int> pref(1+n, 0);
    for (int i = 1; i < n; ++i) {
        while (true) {
            if (s[i] == s[len]) {
                ++len;
                break;
            }
            if (len == 0) {
                break;
            }
            len = pref[len];
        }
        pref[i+1] = len;
    }
    return pref;
}

int solve(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) {
        return -1;
    }
    const int n = a.size();
    int max_pref = prefix(b+'#'+a).back();
    for (int i = 0; i < n - max_pref; ++i) {
        if (a[i] != b[n-i-1]) {
            return -1;
        }
    }
    return n - max_pref;
}

int main() {
    char buf[1+50000];
    scanf("%50000s", buf);
    std::string a(buf);
    scanf("%50000s", buf);
    std::string b(buf);
    int answ = solve(a, b);
    if (answ == -1) {
        printf("No\n");
    } else {
        printf("Yes\n%d\n", answ);
    }
    return 0;
}