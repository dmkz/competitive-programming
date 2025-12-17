#include <bits/stdc++.h>
#define isz(x)(int)(x).size()
using pii = std::pair<int, int>;
int sum(int x) {
    return x < 10 ? x : x % 10 + sum(x / 10);
}
void solve() {
    int n; std::cin >> n;
    assert(n <= 10000);
    std::cout << "9999 9999\n";
}
void research() {
    // здесь мы переберём все пары (a, d) и посмотрим какой максимальной длины
    // сможем достичь. Результат: a = 9999, d = 9999 имеют длину n = 10000
    const pii undef{};
    std::map<int, pii> res;
    for (int d = 1; d <= 1000; d++) {
        for (int a = 1; a <= 1000; a++) {
            std::vector<int> s{sum(a), sum(a+d)};
            for (int n = 3; n <= (int)1e4; n++) {
                int delta = s[isz(s)-1] - s[isz(s)-2];
                int last = sum(a+(n-1)*d);
                if (last - s.back() == delta) {
                    s.push_back(last);
                } else {
                    break;
                }
            }
            for (int sz = isz(s); sz >= 1 && res[sz] == undef; sz--) {
                res[sz] = {a, d};
                if (sz == isz(s))
                    std::cout << "(" << a << ", " << d << "): n = " << sz << std::endl;
            }
        }
    }
}
main() {
    //research();
    solve();
}
