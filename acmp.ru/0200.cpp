// факторизация, факториал, комбинаторика
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using vpii = vector<pii>;
vpii factor(int k) {
// раскладываем число k на простые множители
    vpii res;
    for (int x = 2; x * x <= k; x++)
        if (k % x == 0) {
            if (res.empty() || res.back().first != x)
                res.emplace_back(x, 0);
            res.back().second++;
            k /= x;
            while (k % x == 0) {
                res.back().second++;
                k /= x;
            }
        }
    if (k > 1)
        res.emplace_back(k, 1);
    return res;
}
// сколько раз число n! делится нацело на p:
// [n/p] + [n/p^2] + [n/p^3] + ...
int64_t countInFact(int n, int p) {
    int64_t res{};
    for (int x = 1; x <= n / p; ) {
        x *= p;
        res += n / x;
    }
    return res;
}
main() {
    int n, k;
    cin >> n >> k;
    // раскладываем число k на простые
    auto divK = factor(k);
    // для каждого простого из k считаем, сколько раз он входит в n!:
    // ответ: минимум из (powerInN[p] / powerInK[p])
    int64_t result = (int64_t)1e18L;
    for (const auto &[p, t] : divK) {
        int64_t powN = countInFact(n, p);
        result = min<int64_t>(result, powN / t);
    }
    cout << result << endl;
}
