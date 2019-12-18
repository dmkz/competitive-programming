/*
    Problem: 295C. Greg and Friends
    Solution: graphs, combinatorics, bfs, O(n^4)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
// Modular arithmetic:
template<int mod>
struct Number {
    int data;
    Number(int data_ = 0) : data(data_) { }
    Number& operator+=(Number other) {
        data += other.data;
        if (data >= mod) data -= mod;
        return *this;
    }
    Number operator+(Number other) const {
        return other += *this;
    }
    Number operator*(Number other) const {
        return Number{int(1LL * data * other.data % mod)};
    }
    Number& operator*=(Number other) {
        return *this = *this * other;
    }
};
template<typename T>
T pow(T a, int n) {
    T r = 1;
    while (n > 0) {
        if (n % 2) r *= a;
        a *= a;
        n >>= 1;
    }
    return r;
}
// Solution data:
const int mod = (int)1e9+7;
using Int = Number<mod>;
using pii = std::pair<int,int>;
const int NMAX = 50, INF = mod;
Int fact[NMAX+1], ifact[NMAX+1];
Int C(int n, int k) { return fact[n] * ifact[k] * ifact[n-k]; }
struct State { int side, n50, n100; };
// Solution:
pii solve(const int w, const int N50, const int N100) {
    static int dist[2][NMAX+1][NMAX+1];
    static Int paths[2][NMAX+1][NMAX+1];
    std::fill(&dist[0][0][0],&dist[0][0][0]+(2*(NMAX+1)*(NMAX+1)), INF);
    std::fill(&paths[0][0][0],&paths[0][0][0]+(2*(NMAX+1)*(NMAX+1)), Int(0));
    dist[0][N50][N100] = 0;
    paths[0][N50][N100] = 1;
    std::queue<State> queue;
    queue.push({0,N50,N100});
    while (isz(queue)) {
        auto curr = queue.front();
        queue.pop();
        const int nextSide = 1 - curr.side, currDist = dist[curr.side][curr.n50][curr.n100];
        const Int currPaths = paths[curr.side][curr.n50][curr.n100];
        for (int n50 = 0; n50 <= curr.n50; n50++) {
            for (int n100 = 0; n100 <= curr.n100; n100++) {
                if (n50 + n100 == 0) continue;
                if (50 * n50 + 100 * n100 > w) continue;
                const int nextN50 = N50 - (curr.n50 - n50);
                const int nextN100 = N100 - (curr.n100 - n100);
                int& nextDist = dist[nextSide][nextN50][nextN100];
                Int& nextPaths = paths[nextSide][nextN50][nextN100];
                const bool needPush = (nextDist == INF);
                if (nextDist < currDist + 1) continue;
                nextDist = currDist + 1;
                nextPaths += currPaths * C(curr.n50, n50) * C(curr.n100, n100);
                State next{nextSide,nextN50,nextN100};
                if (needPush) queue.push(next);
            }
        }
    }
    int d = -1, p = paths[1][N50][N100].data;
    if (dist[1][N50][N100] < INF) { d = dist[1][N50][N100]; }
    return {d,p};
}

int main() {
    // Precalc factorials:
    fact[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fact[i] = fact[i-1] * i;
    }
    ifact[NMAX] = pow(fact[NMAX], mod-2);
    for (int i = NMAX-1; i >= 0; i--) {
        ifact[i] = ifact[i+1] * (i+1);
    }
    // Solution:
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, w; std::cin >> n >> w; ) {
        int n50 = 0, n100 = 0;
        for (int v, i = 0; i < n; i++) {
            std::cin >> v;
            n50 += (v == 50);
            n100 += (v == 100);
        }
        auto answ = solve(w, n50, n100);
        std::cout << answ.first << '\n' << answ.second << std::endl;
    }
    return 0;
}