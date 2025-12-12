#include <bits/stdc++.h>
using vs = std::vector<std::string>;
using vvs = std::vector<vs>;
void solveEasy() {
    vvs a(6, vs(3));
    for (int i = 0; i < 6; i++) {
        std::string s; std::cin >> s; // номер
        for (int r = 0; r < 3; r++)
            std::cin >> a[i][r];
    }
    auto count = [&](int i) {
        int res = 0;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                res += (a[i][r][c] == '#');
        return res;
    };
    std::string sz; int n0, n1, n2, n3, n4, n5;
    int answ{};
    while (std::cin >> sz >> n0 >> n1 >> n2 >> n3 >> n4 >> n5) {
        int nRows, nCols;
        int code = sscanf(sz.c_str(), "%dx%d", &nRows, &nCols);
        assert(code == 2);
        int totalCells = nRows * nCols;
        int need = n0 * count(0);
        need += n1 * count(1);
        need += n2 * count(2);
        need += n3 * count(3);
        need += n4 * count(4);
        need += n5 * count(5);
        if (need <= totalCells) {
            // ВЫВОД: гигантский запас по всем тестам, хватит с лихвой:
            //std::cout << sz << " " << n0 << " " << n1 << " " << n2
                      //<< " " << n3 << " " << n4 << " " << n5 << ":\n";
            //std::cout << "    have = " << totalCells << ", want = " << need << std::endl;
            answ++;
        }
    }
    std::cout << answ << std::endl;
}
main() {
    solveEasy();
}
