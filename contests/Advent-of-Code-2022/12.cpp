#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
void setmin(auto &x, const auto &y) {
    if (x > y) x = y;
}
using vs = std::vector<std::string>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const int INF = (int)1e9+7;
vs a;
int sRow, sCol, eRow, eCol;
void readMap() {
    a.clear();
    std::string s;
    while(std::cin >> s) {
        a.push_back(s);
        const int row = isz(a)-1;
        for (int col = 0; col < isz(s); col++) {
            if (a[row][col] == 'S')
                a[row][col] = 'a', sRow = row, sCol = col;
            if (a[row][col] == 'E')
                a[row][col] = 'z', eRow = row, eCol = col;
        }
    }
}
template<bool reversed = false>
vvi bfs(int startRow, int startCol) {
    const int nRows = isz(a), nCols = isz(a[0]);
    vvi dist(nRows, vi(nCols, INF));
    using tiii = std::tuple<int,int,int>;
    std::queue<tiii> q;
    q.push({startRow,startCol,0});
    while (isz(q)) {
        auto [r,c,d] = q.front();
        q.pop();
        if (dist[r][c] <= d)
            continue;
        dist[r][c] = d;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr * dr + dc * dc != 1) continue;
                const int nr = r + dr, nc = c + dc;
                if (nr < 0 || nr >= nRows || nc < 0 || nc >= nCols) continue;
                if (
                    (!reversed && a[nr][nc] <= a[r][c] + 1) ||
                    (reversed && a[nr][nc] >= a[r][c] - 1))
                    q.push({nr,nc,d+1});
            }
        }
    }
    return dist;
}
int part1() {
    return bfs(sRow,sCol)[eRow][eCol];
}
int part2() {
    vvi dist = bfs<true>(eRow,eCol);
    int answ = INF;
    for (int r = 0; r < isz(a); r++)
        for (int c = 0; c < isz(a[r]); c++)
            if (a[r][c] == 'a')
                setmin(answ, dist[r][c]);
    return answ;
}
int main() {
    readMap();
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}