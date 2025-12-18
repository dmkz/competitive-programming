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
/*
    Результаты:
    (1, 1): n = 9
    (10, 1): n = 10
    (19, 99): n = 20
    (29, 99): n = 30
    (39, 99): n = 40
    (49, 99): n = 50
    (59, 99): n = 60
    (69, 99): n = 70
    (79, 99): n = 80
    (89, 99): n = 90
    (99, 99): n = 100
    (199, 999): n = 200
    (299, 999): n = 300
    (399, 999): n = 400
    (499, 999): n = 500
    (599, 999): n = 600
    (699, 999): n = 700
    (799, 999): n = 800
    (899, 999): n = 900
    (999, 999): n = 1000
*/
main() {
    //research();
    solve();
}
