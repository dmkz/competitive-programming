#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем число доступных единичных квадратов.
    int64_t n; cin >> n;
    // low подходит, high не подходит. При такой high квадрат mid помещается в int64_t.
    int64_t low = 1, high = 2'000'000'000LL;
    while (high - low > 1) {
        int64_t mid = (low + high) / 2;
        if (mid * mid <= n) low = mid;
        else high = mid;
    }
    cout << low << '\n';
}