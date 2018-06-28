/*
    "Покорение вселенной": обработка строк, простые числа
*/

#include <stdio.h>
#include <string>
#include <cassert>

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return n > 1;
}

int main() {
    char buf[500000+1];
    scanf("%500000s", buf);
    std::string s(buf);
    const int n = (int)s.size();
    
    // Дешифрование:
    std::string f(n, '?');
    int rs = n-1, ls = 0, len = 1, lf = 0, rf = n-1;
    while (ls <= rs) {
        if (len % 2 == 1) {
            for (int i = std::max(rs-len+1, ls); i <= rs; ++i) {
                f[lf++] = s[i];
            }
            rs -= len;
        } else {
            for (int i = std::min(rs, ls+len-1); i >= ls; --i) {
                f[rf--] = s[i];
            }
            ls += len;
        }
        ++len;
    }
    
    // Формирование ответа:
    std::string answ;
    int p = 0, id = 0;
    while (p < n) {
        assert('A' <= f[p] && f[p] <= 'Z');
        ++id;
        int r = p+1;
        while (r < n && !('A' <= f[r] && f[r] <= 'Z')) {
            ++r;
        }
        if (is_prime(id)) {
            answ += f.substr(p, r-p);
        }
        p = r;
    }
    if (answ.empty()) {
        answ = "Impossible";
    }
    printf("%s\n", answ.c_str());
    return 0;
}