#include <bits/stdc++.h>
using ld = long double;
main() {
    int u, m;
    while(std::cin >> u >> m) {
        std::vector<ld> sum(4+1);
        for (int count = 15; count --> 0; ) {
            int t, s; std::cin >> t >> s;
            ld cost = ld(s) / t;
            for (int i = 1; i <= t; i++)
                sum[i] += cost;
            for (int i = t+1; i <= 4; i++)
                sum[i] += m;
        }
        for (int t = 1; t <= 4; t++) {
            ld answ = sum[t];
            if (answ >= u)
                answ += (answ - u);
            std::cout << answ << std::endl;
        }
    }
}
