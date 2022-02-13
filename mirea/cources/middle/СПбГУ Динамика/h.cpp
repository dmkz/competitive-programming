#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
int main() {
    freopen("peacefulsets.in","rt",stdin);
    freopen("peacefulsets.out","wt",stdout);
    // считаем динамику:
    const int MAX = 2020;
    vector dp(MAX, vector(MAX, 0LL));
    fill(dp[0].begin(),dp[0].end(),1);
    // dp[sum][max] = сколько есть мирных множеств суммой sum если максимум <= max?
    for (int sum = 1; sum < MAX; sum++)
        for (int mx = 1; mx < MAX; mx++)
            // переходы:
            // если элемент mx не входит в множество суммой sum, то это dp[sum][mx-1]
            // иначе mx входит в множество суммой sum и мы должны составить множество
            // суммой sum-mx, максимум в котором не превосходит mx/2: dp[sum-mx][mx/2]
            dp[sum][mx] = dp[sum][mx-1] + (mx <= sum ? dp[sum-mx][mx/2] : 0);
    int s; cin >> s;
    cout << dp[s][s] << endl;
}