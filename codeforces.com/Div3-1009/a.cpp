#include <bits/stdc++.h>
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // диагонали должны быть равными, тогда это квадрат
        // но конкретно в этой задаче условие сильнее: должны
        // быть равны половинки диагоналей между собой (чтобы угол был 90)
        int l, r, d, u; std::cin >> l >> r >> d >> u;
        std::cout << (l == r && l == d && l == u ? "Yes\n" : "No\n");
    }
}
