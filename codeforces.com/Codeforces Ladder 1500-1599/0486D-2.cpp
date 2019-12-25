/*
    Problem: 486D. Valid Sets
    Solution: dynamic programming, brute force, combinatorics, trees, dfs, math, O(n^2)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define reuniq(x) (x).erase(std::unique(all(x)), (x).end())
template<int mod> 
struct IntMod {
    int val;
    IntMod(int val_ = 0) : val(val_) { }
    IntMod& operator+=(IntMod a) { return (val += a.val) >= mod ? (val -= mod, *this) : *this; }
    IntMod& operator-=(IntMod a) { return (val -= a.val) <    0 ? (val += mod, *this) : *this; }
    IntMod operator+(IntMod a) const { return IntMod(*this) += a; }
    IntMod operator-(IntMod a) const { return IntMod(*this) -= a; }
    IntMod operator*(IntMod a) const { return IntMod(int(val * 1LL * a.val % mod)); }
    IntMod& operator*=(IntMod a) { return *this = *this * a; }
};
template<int mod> std::ostream& operator<<(std::ostream& os, IntMod<mod> intmod) { return os << intmod.val; }
// solution
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
const int NMAX = 2048;
int d, n, arr[NMAX];
std::vector<int> adj[NMAX];
Int dp[2][2][NMAX];
const int WAS = 1, INCLUDE = 1;
std::vector<Int> stack;
void dfs(const int u, const int p, const int max) {
    int nChild = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, max);
        nChild++;
    }
    // dp[WAS][!INCLUDE][u] = sum(dp[WAS][!INCLUDE][v] + dp[WAS][INCLUDE][v])
    for (int v : adj[u]) {
        if (v == p) continue;
        dp[WAS][!INCLUDE][u] += dp[WAS][!INCLUDE][v] + dp[WAS][INCLUDE][v];
    }
    if (arr[u] < max - d || arr[u] > max) return;
    dp[!WAS][INCLUDE][u] = (arr[u] != max);
    for (int v : adj[u]) {
        if (v == p) continue;
        dp[!WAS][INCLUDE][u] *= dp[!WAS][INCLUDE][v] + 1;
    }
    // dp[WAS][INCLUDE][u]
    stack = {1};
    for (int i = isz(adj[u]) - 1; i >= 0; i--) {
        const int v = adj[u][i];
        if (v == p) continue;
        stack.push_back(stack.back() * (dp[WAS][INCLUDE][v] + dp[!WAS][INCLUDE][v] + 1));
    }
    Int left(1);
    for (int v : adj[u]) {
        if (v == p) continue;
        stack.pop_back();
        dp[WAS][INCLUDE][u] += left * dp[WAS][INCLUDE][v] * stack.back();
        left *= dp[!WAS][INCLUDE][v] + 1;
    }
    if (arr[u] == max) {
        dp[WAS][INCLUDE][u] += left;
    }
}
int main() {
    std::cin >> d >> n;
    for (int i = 1; i <= n; i++) std::cin >> arr[i];
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    std::vector<int> values(arr+1,arr+n+1);
    std::sort(all(values));
    reuniq(values);
    Int answ(0);
    for (int max : values) {
        std::fill(&dp[0][0][0], &dp[0][0][0] + 2 * 2 * NMAX, 0);
        dfs(1,0,max);
        answ += dp[WAS][INCLUDE][1] + dp[WAS][!INCLUDE][1];
    }
    std::cout << answ << std::endl;
    return 0;
}