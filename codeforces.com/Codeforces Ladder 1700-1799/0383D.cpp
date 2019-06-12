/*
    Problem: 383D. Antimatter
    
    Solution: dynamic programming, divide and conquer, combinatorics, O(n * log(n) * SUM)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) std::size(x)
#define io_sync_off std::ios_base::sync_with_stdio(0); std::cin.tie(0)
// Debug defines:
#define watch(x) std::cerr << std::setw(12) << #x << " = " << std::setw(12) << x
#define watchln(x) watch(x) << std::endl
#define watchsp(x) watch(x) << " "
#define cerr cerr && debug && std::cerr
const int debug = 0;
namespace std {
    // 2D arrays:
    template<typename T, int N, int M> auto size(const T (&a)[N][M]) { return N * M; }
    template<typename T, int N, int M> auto begin(T (&a)[N][M]) { return &a[0][0]; }
    template<typename T, int N, int M> auto end(T (&a)[N][M]) { return &a[0][0] + N * M; }
    // Algorithms:
    template<typename C> void reuniq(C& c) { c.erase(unique(c), end(c)); }
    template<typename C, typename X> int lowpos(C& c, X& x) {
        return int(lower_bound(all(c), x) - begin(c));
    }
    template<typename X, typename Y> X& remin(X& x, Y& y) { return x = (y < x) ? y : x; }
    template<typename X, typename Y> X& remax(X& x, Y& y) { return x = (x < y) ? y : x; }
}
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<ll> vl;
typedef std::vector<vi> vvi;
typedef std::vector<vl> vvl;
typedef std::pair<int,int> pii;
typedef std::pair<int,ll> pil;
typedef std::pair<ll,int> pli;
typedef std::pair<ll,ll> pll;

const int mod = (int)1e9+7, SMAX = 20020, NMAX = 1010, MID = 10000;
int a[NMAX], n;
ull dp[NMAX][SMAX], ls[SMAX][2], rs[SMAX][2], POW64 = 1;
void add(ull& high, ull& low, ull what) {
    auto was = low;
    low += what;
    high += was > low;
}
template<const int dir, typename T, const int N, const int M>
void calc(int begin, int end, T (&sums)[N][M]) {
    std::fill(all(dp[begin]),0);
    std::fill(all(sums),0);
    sums[+a[begin] + MID][1] = 1;
    sums[-a[begin] + MID][1] = 1;
    dp[begin][+a[begin] + MID] = 1;
    dp[begin][-a[begin] + MID] = 1;
    for (int i = begin+dir; i != end; i += dir) {
        for (int s = 0; s < SMAX; s++) {
            dp[i][s] = (s + a[i] < SMAX ? dp[i-dir][s + a[i]] : 0) +
                (s - a[i] >= 0 ? dp[i-dir][s - a[i]] : 0);
            add(sums[s][0], sums[s][1], dp[i][s]);
        }
        if (i + 1 == end || (i - begin) % 20 == 0) {
            for (int s = 0; s < SMAX; s++) {
                dp[i][s] %= mod;
            }
        }
    }
}
ull get(int begin, int end) {
    if (begin == end) { return 0; }
    int mid = (begin + end) / 2;
    calc<-1>(mid, begin-1, ls);
    calc<+1>(mid+1, end+1, rs);
    ull res = 0;
    for (int s = -MID; s <= MID; s++) {
        ull leftCnt = (ls[s+MID][0] * POW64 + ls[s+MID][1] % mod) % mod;
        ull rightCnt = (rs[MID-s][0] * POW64 + rs[MID-s][1] % mod) % mod;
        res += leftCnt * rightCnt;
        if ((s + MID) % 8 == 0) { res %= mod; }
    }
    return (res + get(begin, mid) + get(mid+1,end)) % mod;
}
int main() {
    io_sync_off;
    POW64 = 1; for (int i = 1; i <= 64; i++) { (POW64 *= 2) %= mod; }
    std::cin >> n;
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    std::cout << get(0, n-1) << std::endl;
    return 0;
}