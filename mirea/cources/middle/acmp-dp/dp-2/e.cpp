#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
vector<int> readArray() {
    int n, a0, k, b, m;
    cin >> n >> a0 >> k >> b >> m;
    vector<int> a(n, a0 % m);
    for (int i = 1; i < n; i++)
        a[i] = int((a[i-1] * 1LL * k + b) % m);
    return a;
}
using pii = pair<int,int>;
int main() {
    auto a = readArray();
    int n = (int)a.size();
    // dp[длина] => {минимальный конец, его индекс}
    vector<pair<int,int>> dp(n+2, {inf, 0});
    dp[0] = {-inf, -1};
    vector<int> prev(n, -1);
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), pii(a[i], 0));
        int len = int(it - dp.begin());
        prev[i] = dp[len-1].second;
        *it = min(*it, pii(a[i], i));
    }
    // восстановление ответа
    // 1. находим длину подпоследовательности в ответе:
    // найти последнюю не бесконечность:
    int bestAnswerLen = 0;
    while (dp[bestAnswerLen+1].first != inf)
        bestAnswerLen++;
    // чем оканчивается лучшая последовательность?
    int last = dp[bestAnswerLen].second;
    vector<int> answ;
    while (bestAnswerLen > 0) {
        answ.push_back(a[last]);
        last = prev[last];
        bestAnswerLen--;
    }
    reverse(answ.begin(), answ.end());
    for (auto it : answ)
        cout << it << ' ';
    cout << endl;
}