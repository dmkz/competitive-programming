/*
    Problem: 797B. Odd sum
    
    Solution: dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <numeric>
#include <cmath>

#define ios_fast std::ios_base::sync_with_stdio(0); \
std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

#define  input(x) for (auto& it : (x)) std::cin >> it
#define    all(x) (x).begin(), (x).end()
#define   size(x) (int)((x).size())
#define unique(x) (x).erase(std::unique(all((x))), (x).end())

const int mod = (int)1e9+7;
typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<ll> vll;

void update(int& a, int b) {
    a = std::max(a,b);
}

int main() {
    ios_fast;
    int n; std::cin >> n;
    vi arr(n); input(arr);
    const int INF = (int)1e9+1;
    vvi dp(2, vi(1+n,-INF));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        int nw = dp[0][i] + arr[i];
        dp[0][i+1] = dp[0][i];
        dp[1][i+1] = dp[1][i];
        update(dp[std::abs(arr[i]) % 2][i+1], arr[i]);
        update(dp[std::abs(nw) % 2][i+1], nw);
        nw = dp[1][i] + arr[i];
        update(dp[std::abs(nw) % 2][i+1], nw);
    }
    std::cout << dp[1][n];
    return 0;
}