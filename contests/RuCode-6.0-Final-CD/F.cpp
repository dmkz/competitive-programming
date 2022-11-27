#include <bits/stdc++.h>

bool check(int64_t a, int64_t b, int64_t c) {
    int64_t as = a*a;
    int64_t bs = b*b;
    int64_t cs = c*c;
    return as != 0 && bs != 0 && cs != 0 && (as+bs == cs || as+cs==bs || cs+bs==as);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int64_t a,b,c; std::cin >> a >> b >> c;
    int64_t ans = -1;
    for (int64_t i = 1000000; i >= -1000001; --i) {
        if (check(a+i, b+i, c+i)) {
            ans = i;
            break;
        }
    }
    if (ans != -1) {
        std::cout << "Possible\n" << ans;
    } else {
        std::cout << "Impossible";
    }
    return 0;
}
