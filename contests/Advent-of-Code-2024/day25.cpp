#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

main() {
    std::string s;
    std::vector a(1,std::vector<std::string>{});
    while (std::getline(std::cin, s)) {
        if (s.empty())
            a.push_back({});
        else
            a.back().push_back(s);
    }
    std::vector<std::vector<int>> keys, locks;
    for (const auto &map : a) {
        bool isKey = (map[0][0] == '.');
        const int nCols = isz(map[0]);
        std::vector<int> h(nCols,-1);
        for (int r = 0; r < isz(map); r++)
            for (int c = 0; c < nCols; c++)
                if (map[r][c] == '#')
                    h[c]++;
        if (isKey)
            keys.emplace_back(h);
        else
            locks.emplace_back(h);
    }
    int answ{};
    for (const auto &a : locks) {
        for (auto b : keys) {
            assert(isz(b) == isz(a));
            bool ok = 1;
            for (int i = 0; i < isz(b); i++) {
                b[i] += a[i];
                ok &= (b[i] <= 5);
            }
            answ += ok;
        }
    }
    std::cout << answ << std::endl;
}
