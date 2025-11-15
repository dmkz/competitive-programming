// Решение: конструктив
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using vs = std::vector<std::string>;
int solve() {
    std::string s; std::cin >> s;
    if (s.size() == 1u)
        return 1;
    for (auto t : vs{"**", "*<", ">*", "><"}) {
        auto p = s.find(t);
        if (p != s.npos)
            return -1;
    }
    // осталась строка вида: <<<<<<*>>>>
    int nLess = 0, nAny = 0, nGreater = 0;
    int i = 0;
    while (i < isz(s) && s[i] == '<') {
        nLess++;
        i++;
    }
    while (i < isz(s) && s[i] == '*') {
        nAny++;
        i++;
    }
    while (i < isz(s) && s[i] == '>') {
        nGreater++;
        i++;
    }
    return std::max(nLess, nGreater) + nAny;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << "\n";
}
