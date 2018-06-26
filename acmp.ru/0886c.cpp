/*
    "Суффиксы": минимальный период, префикс-функция, O(n)
*/

#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

int solve(const std::string& s) {
    const int n = s.size();
    std::vector<int> prefix(1+n, 0);
    int len = 0;
    for (int i = 1; i < n; ++i) {
        while (true) {
            if (s[i] == s[len]) {
                len++;
                break;
            }
            if (len == 0) {
                break;
            }
            len = prefix[len];
        }
        prefix[i+1] = len;
    }
    while (true) {
        int period = n - len;
        if (n % period == 0) {
            return n / period;
        }
        len = prefix[len];
    }
}

int main() {
    char buf[100000+1];
    scanf("%100000s", buf);
    printf("%d", solve(buf));
    return 0;
}