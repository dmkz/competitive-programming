#include <bits/stdc++.h>
/*
    Стреляем по диагоналям так, чтобы ни один 1х5 не был пропущен ни вертикально, ни горизонтально:
    ....o....o....o....o....o....o....o....o
    o....o....o....o....o....o....o....o....
    .o....o....o....o....o....o....o....o...
    ..o....o....o....o....o....o....o....o..
    ...o....o....o....o....o....o....o....o.
    ....o....o....o....o....o....o....o....o
    o....o....o....o....o....o....o....o....
    .o....o....o....o....o....o....o....o...
    ..o....o....o....o....o....o....o....o..
    ...o....o....o....o....o....o....o....o.
    ....o....o....o....o....o....o....o....o
    o....o....o....o....o....o....o....o....
    .o....o....o....o....o....o....o....o...
    ..o....o....o....o....o....o....o....o..
    ...o....o....o....o....o....o....o....o.
    ....o....o....o....o....o....o....o....o
    o....o....o....o....o....o....o....o....
    .o....o....o....o....o....o....o....o...
    ..o....o....o....o....o....o....o....o..
    ...o....o....o....o....o....o....o....o.
*/
const int MISS = 0;
const int HIT = 1;
const int SUNK = 2;
// 7 2
// x1234567
// 1.oooox.
// 2.x.....
// 3.o.....
// 4.x.....
// 5.o.....
// 6.o.....
// 7.......
main() {
    int n, k; std::cin >> n >> k;
    std::vector<std::pair<int,int>> shots;
    int queries = 0;
    auto ask = [&](int row, int col) -> int {
        if (row < 1 || row > n || col < 1 || col > n || k == 0)
            return MISS;
        queries++;
        assert(queries <= 2500);
        std::cout << row << " " << col << std::endl;
        std::string s; std::cin >> s;
        if (s == "hit") {
            shots.emplace_back(row, col);
            return HIT;
        } else if (s == "miss") {
            return MISS;
        } else {
            assert(s == "sunk");
            k--;
            return SUNK;
        }
    };
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
            if (col % 5 == row % 5)
                ask(row+1, col+1);
    // теперь у нас есть ровно k попаданий (или больше)
    assert((int)shots.size() >= k);
    const int dr[] = {-1, 0, +1, 0};
    const int dc[] = {0, -1, 0, +1};
    auto candidates = shots;
    for (const auto &[r, c] : candidates) {
        for (int dir = 0; dir < 4; dir++) {
            int nr = r, nc = c, steps = 4;
            while (steps > 0) {
                nr += dr[dir];
                nc += dc[dir];
                steps--;
                ask(nr, nc);
            }
        }
    }
}
