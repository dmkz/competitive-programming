#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
const int INF = (int)1e9;
using vi = vector<int>;
using vvi = vector<vi>;
void setmax(auto &x, auto y) { if (y > x) x = y; }
int main() {
    //freopen("slalom.in", "rt", stdin);
    //freopen("slalom.out", "wt", stdout);
    int n; cin >> n;
    vvi dp(n,vi(n,-INF));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            int a; cin >> a;
            if (i - 1 >= 0) {
                if (j < i) setmax(dp[i][j],dp[i-1][j]+a);
                if (j > 0) setmax(dp[i][j],dp[i-1][j-1]+a);
            } else dp[i][j] = a;
        }
    }
    cout << *max_element(all(dp.back())) << endl;
}