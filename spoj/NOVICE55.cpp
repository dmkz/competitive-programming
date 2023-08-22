/*
    problem: NOVICE55 - Grid painting
    solution: game theory, brute force, oeis, xor
*/
#include <bits/stdc++.h>
using vi = std::vector<int>;
vi precalc()
{
    /*
        The optimal strategies for this game can be determined by computing the nim-value nv(N) of each board 1 X N:
        nv(0) = 0
        nv(1) = 0
        nv(N+2) = least nonnegative integer not in {nimsum(nv(k),nv(N-k)) : k <= N}
        (where nimsum(a,b) is the bitwise xor of a and b).
        The second player wins a game iff its nim-value is 0.
    */
    auto nimsum = [&](int a, int b) { return a^b; };
    const int nmax = 10000;
    vi nv(nmax+1);
    for (int n = 0; n+2 <= nmax; n++) {
        std::bitset<nmax+1> bs;
        bs.flip();
        for (int k = 0; k <= n-k; k++) {
            int bit = nimsum(nv[k],nv[n-k]);
            bs[bit] = 0;
        }
        nv[n+2] = bs._Find_first();
    }
    return nv;
}

int main() {
    vi nv = precalc();
    int tt; std::cin >> tt;
    while (tt --> 0) {
        int n; std::cin >> n;
        std::cout << (nv[n] == 0 ? "Akash" : "Aayush") << std::endl;
    }
    return 0;
}
