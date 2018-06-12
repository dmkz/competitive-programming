#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> prefix(const std::string& s) {
// Нахождение префикс-функции от строки s за линейное время
    const int n = (int)s.size();
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

int main() {
    static char buf[1+1000000];
    scanf("%1000000s", buf);
    auto pref = prefix(buf);
    for (int i = 1; i < (int)pref.size(); ++i) {
        printf("%d ", pref[i]);
    }
    return 0;
}