#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = (ll)1e18L;
void setmax (auto &x, const auto &y) { if (x < y) x = y; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение данных:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &item : a)
        cin >> item;
    int k; cin >> k;
    // считаем суффикс-суммы, чтобы быстро говорить сумму на отрезке:
    vector<ll> sum(n+1);
    for (int i = n-1; i >= 0; i--)
        sum[i] = sum[i+1] + a[i];
    // функция для суммы на отрезке:
    auto getSum = [&](int L, int R) -> ll {
        return L > R ? 0 : sum[L] - sum[R+1];
    };
    // считаем динамику рекурсивно:
    vector dp(n, vector<int64_t>(k+1, -1));
    // в динамике будет лежать макс. разница между набранными первым и вторым игроками
    function<ll(int, int)> solve = [&](int i, int x) -> ll {
        // находим ответ при условии что остались стопки i, i+1, i+2, ..., n-1
        // среди которых мы можем взять 1, 2, 3, ..., x
        if (i >= n) // стопок больше не осталось, ответ равен нулю
            return 0;
        if (dp[i][x] != -1)
            return dp[i][x]; // ответ уже посчитан
        ll res = -inf;
        for (int j = i; j < n && j - i + 1 <= x; j++) {
            // берём стопки с i-й по j-ю
            setmax(res, getSum(i, j) - solve(j+1, j-i+1));
        }
        return dp[i][x] = res;
    };
    ll diff = solve(0, k);
    ll sumA = sum[0];
    // score1 - score2 == diff
    // score1 + score2 = sumA
    // 2 * score1 = diff + sumA
    // score1 = (diff + sumA) / 2
    cout << (diff + sumA) / 2 << endl;
}
