#include <bits/stdc++.h>
using namespace std;
int64_t sumSquares(int64_t k) {
    return k * (k + 1) * (2 * k + 1) / 6;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Ищем последнее k, для которого хватает квадратов на все фигуры от 1 до k.
    int64_t n; cin >> n;
    int64_t low = 0, high = 1'500'000;
    while (high - low > 1) {
        int64_t mid = (low + high) / 2;
        if (sumSquares(mid) <= n) low = mid;
        else high = mid;
    }
    cout << low << '\n';
}