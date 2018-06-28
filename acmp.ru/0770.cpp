/*
    "Покорение вселенной": обработка строк, решето Эратосфена, O(n)
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

bool is_prime(int n) {
    static bool evaluated = false;
    static const int MAX_N = 500000;
    static std::vector<bool> prime(1+MAX_N, true);
    if (!evaluated) {
        prime[1] = prime[0] = false;
        for (int i = 2; i * i <= MAX_N; ++i) {
            if (!prime[i]) {
                continue;
            }
            for (int j = i * i; j <= MAX_N; j += i) {
                prime[j] = false;
            }
        }
        evaluated = true;
    }
    return prime[n];
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