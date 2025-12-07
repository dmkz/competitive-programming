#include <bits/stdc++.h>
void solveEasy() {
    std::string s;
    std::vector<std::string> a;
    while (std::getline(std::cin, s))
        if (!s.empty())
            a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    int answ = 0;
    for (int r = 1; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            if (!(a[r-1][c] == '|' || a[r-1][c] == 'S'))
                continue;
            if (a[r][c] == '^') {
                if (c-1 >= 0) a[r][c-1] = '|';
                if (c+1 < nCols) a[r][c+1] = '|';
                answ++;
            } else if (a[r][c] == '.') {
                a[r][c] = '|';
            }
        }
    }
    std::cout << answ << std::endl;
}
using ll = long long;
void solveHard() {
    std::string s;
    std::vector<std::string> a;
    while (std::getline(std::cin, s))
        if (!s.empty())
            a.push_back(s);
    const int nRows = (int)a.size();
    const int nCols = (int)a[0].size();
    std::vector cache(nRows, std::vector<ll>(nCols, -1));
    std::function<ll(int,int)> dfs = [&](int r, int c) -> ll {
        if (r >= nRows)
            return 1;
        if (cache[r][c] != -1)
            return cache[r][c];
        ll res = 0;
        if (r+1 < nRows && a[r+1][c] == '^') {
            res = dfs(r+1, c-1) + dfs(r+1, c+1);
        } else {
            res = dfs(r+1, c);
        }
        return cache[r][c] = res;
    };
    int startCol = (int)a[0].find('S');
    std::cout << dfs(0, startCol) << std::endl;
}
main() {
    solveHard();
}
