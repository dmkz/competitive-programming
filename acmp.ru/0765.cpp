/*
    Задача: 765. Го
    
    Решение: графы, поиск в глубину, компоненты связности, O(n^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;
int main() {
    for (int n; std::cin >> n; ) {
        vs field(n);
        for (int i = 0; i < n; ++i) { std::cin >> field[i]; }
        vvi part(n, vi(n, 0));
        int nParts = 0, answ = 0;
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (field[row][col] == 'B' && !part[row][col]) {
                    int cur = 0;
                    std::function<void(int,int)> dfs = [&](int r, int c) {
                        if (r < 0 || r >= n || c < 0 || c >= n) { return; }
                        if (part[r][c] == nParts || field[r][c] == 'W') { return; }
                        part[r][c] = nParts;
                        if (field[r][c] == '.') { cur++; return; }
                        for (int dr = -1; dr <= 1; ++dr) {
                            for (int dc = -1; dc <= 1; ++dc) {
                                if (dr * dr + dc * dc == 1) {
                                    dfs(r+dr, c+dc);
                                }
                            }
                        }
                    };
                    ++nParts;
                    dfs(row,col);
                    answ += (cur == 1);
                }
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}