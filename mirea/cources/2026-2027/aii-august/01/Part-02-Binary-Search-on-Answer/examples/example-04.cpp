#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Храним все возможные расходы, не превосходящие ограничение на n.
    vector<int64_t> sums = {0};
    for (int64_t k = 1; sums.back() + k * k <= 1'000'000'000'000'000'000LL; k++)
        sums.push_back(sums.back() + k * k);
    // Отвечаем на запрос последним расходом, не превосходящим n.
    int64_t n; cin >> n;
    cout << upper_bound(sums.begin(), sums.end(), n) - sums.begin() - 1 << '\n';
}