#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using vvi = std::vector<vi>;
int sign(auto x) {
    if (x < 0) return -1;
    if (x > 0) return +1;
    return 0;
}
int lowpos(const auto &v, const auto &x) {
    return int(std::lower_bound(all(v), x) - v.begin());
}
void solveEasy() {
    std::string s;
    std::vector<std::pair<int,int>> pt;
    ll answ{};
    while (std::getline(std::cin, s)) {
        if (s.empty()) break;
        int x, y;
        int code = sscanf(s.c_str(), "%d,%d", &x, &y);
        if (code == 2) {
            for (auto [x1, y1] : pt) {
                int maxX = std::max(x1, x);
                int maxY = std::max(y1, y);
                int minX = std::min(x1, x);
                int minY = std::min(y1, y);
                ll sq = (maxX - minX + 1LL) * (maxY - minY + 1);
                answ = std::max(answ, sq);
            }
            pt.push_back({x, y});
        } else assert(false);
    }
    std::cout << answ << std::endl;
}
struct Coords {
    
    vi coords;
    vpii segs; // храним отрезки в формате [R, L]
    
    void addCoord(int x) {
        coords.push_back(x);
    }
    
    int numSegs() const {
        return isz(segs);
    }
    
    int getSegWidth(int i) const {
        assert(0 <= i && i < numSegs());
        auto [r, l] = segs[i];
        return r - l + 1;
    }
    
    int getSegIndex(int x) const {
        int i = lowpos(segs, pii(x, -1));
        assert(i >= 0);
        assert(i < isz(segs));
        auto [r, l] = segs[i];
        assert(l <= x && x <= r);
        return i;
    }
    
    void build() {
        segs.clear();
        std::sort(all(coords));
        coords.erase(std::unique(all(coords)), coords.end());
        for (int i = 0; i < isz(coords); i++) {
            int curr = coords[i];
            if (i - 1 >= 0) {
                int prev = coords[i-1];
                if (prev+1 <= curr-1)
                    segs.emplace_back(curr-1, prev+1);
            }
            segs.emplace_back(curr, curr);
        }
    }
};
struct PrefixSums2D {
    int nRows, nCols;
    std::vector<std::vector<ll>> sums;
    PrefixSums2D(int nRows_, int nCols_, const auto &getElem)
        : nRows(nRows_), nCols(nCols_), sums(nRows+1, std::vector<ll>(nCols+1))
    {
        for (int i = nRows-1; i >= 0; i--)
            for (int j = nCols-1; j >= 0; j--) {
                sums[i][j] = getElem(i, j);
                sums[i][j] += sums[i+1][j];
                sums[i][j] += sums[i][j+1];
                sums[i][j] -= sums[i+1][j+1];
            }
    }
    ll operator()(int r1, int r2, int c1, int c2) const {
        if (r1 > r2) std::swap(r1, r2);
        if (c1 > c2) std::swap(c1, c2);
        return sums[r1][c1] - sums[r2+1][c1] - sums[r1][c2+1] + sums[r2+1][c2+1];
    }
};
void solveHard() {
    // читаем точки:
    std::string s;
    std::vector<std::pair<int,int>> pt;
    ll answ{};
    while (std::getline(std::cin, s)) {
        if (s.empty()) break;
        int x, y;
        int code = sscanf(s.c_str(), "%d,%d", &y, &x);
        assert(code == 2);
        pt.push_back({x, y});
    }
    // сжимаем координаты:
    Coords coordsX, coordsY;
    for (const auto &[x, y] : pt) {
        coordsX.addCoord(x);
        coordsY.addCoord(y);
    }
    coordsX.build();
    coordsY.build();
    // заменяем координаты прямоугольников сжатыми координатами:
    for (auto &[x, y] : pt) {
        x = coordsX.getSegIndex(x);
        y = coordsY.getSegIndex(y);
    }
    // строим 2D-суффикс суммы для площади:
    const int nX = coordsX.numSegs();
    const int nY = coordsY.numSegs();
    PrefixSums2D square(nX, nY, [&](int ix, int iy) -> ll {
        return coordsX.getSegWidth(ix) * 1LL * coordsY.getSegWidth(iy);
    });
    // отметим только те клетки которые внутри области:
    std::vector map(1+nX+1, std::vector<char>(1+nY+1, '.'));
    int numRows = isz(map);
    int numCols = isz(map[0]);
    
    for (int i = 0; i < isz(pt); i++) {
        int j = (i+1) % isz(pt);
        auto [xi, yi] = pt[i];
        auto [xj, yj] = pt[j];
        xi++, yi++, xj++, yj++; // 1-индексация
        int dx = sign(xj - xi), dy = sign(yj - yi);
        while (!(xi == xj && yi == yj)) {
            map[xi][yi] = 'X';
            xi += dx;
            yi += dy;
        }
        map[xi][yi] = 'X';
    }
    for (const auto &[x, y] : pt)
        map[x+1][y+1] = '#';
    auto printMap = [&](){
        std::cout << "Map:\n";
        for (int i = 0; i < isz(map); i++) {
            for (int j = 0; j < isz(map[i]); j++) {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
    };
    //printMap();
    // найдём компоненты связности:
    int numComponents = 0;
    std::vector components(1, vpii{});
    vvi visited(numRows, vi(numCols, 0));
    std::function<void(int,int)> visit = [&](int i, int j)
    {
        if (i < 0 || i >= numRows) return;
        if (j < 0 || j >= numCols) return;
        if (map[i][j] != '.') return;
        if (visited[i][j]) return;
        visited[i][j] = numComponents;
        components[numComponents].emplace_back(i, j);
        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if (di * di + dj * dj == 1)
                    visit(i + di, j + dj);
    };
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            if (!visited[i][j] && map[i][j] == '.') {
                numComponents++;
                components.push_back({});
                visit(i, j);
            }
    for (int i = 0; i < isz(components); i++)
        for (auto [x, y] : components[i])
            map[x][y] = char('A' + i - 1);
    //printMap();
    assert(numComponents == 2);
    // отметим точки внутри области:
    vvi inside(numRows, vi(numCols));
    for (auto [x, y] : components[2])
        inside[x][y] = 1;
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            if (map[i][j] == 'X' || map[i][j] == '#')
                inside[i][j] = 1;
    //std::cout << "Inside:\n";
    //for (int i = 0; i < numRows; i++) {
    //    for (int j = 0; j < numCols; j++)
    //        std::cout << inside[i][j];
    //    std::cout << std::endl;
    //}
    // подготовим функцию проверки что все точки внутри прямоугольника
    // лежат внутри области:
    PrefixSums2D sumsInside(numRows, numCols, [&](int i, int j) {
        return inside[i][j];
    });
    auto isRectInsideTheShape = [&](int r1, int r2, int c1, int c2) {
        int dr = std::abs(r1 - r2);
        int dc = std::abs(c1 - c2);
        return sumsInside(r1, r2, c1, c2) == (dr + 1) * (dc + 1);
    };
    for (int i = 0; i < isz(pt); i++)
        for (int j = i+1; j < isz(pt); j++) {
            auto [r1, c1] = pt[i];
            auto [r2, c2] = pt[j];
            if (isRectInsideTheShape(r1+1,r2+1,c1+1,c2+1)) {
                answ = std::max(answ, square(r1,r2,c1,c2));
            }
        }
    std::cout << answ << std::endl;
}
main() {
    solveHard();
}
