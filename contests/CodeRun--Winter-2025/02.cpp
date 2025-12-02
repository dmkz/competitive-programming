#include <bits/stdc++.h>
using pii = std::pair<int,int>;
void solve() {
    const int SMAX = 100 * 10;
    std::bitset<1+SMAX> possible;
    possible[0] = 1;
    for (int i = 0; i < 10; i++) {
        int x; std::cin >> x;
        possible |= (possible << x);
    }
    int l = 100;
    while (l >= 0 && !possible[l])
        l--;
    int r = 100;
    while (r <= SMAX && !possible[r])
        r++;
    pii answ = std::min(pii(100-l,-l), pii(r-100,-r));
    std::cout << -answ.second << std::endl;
}
main() {
    solve();
}
