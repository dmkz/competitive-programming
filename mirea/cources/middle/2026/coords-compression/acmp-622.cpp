// сжатие прямоугольников, поиск в ширину, компоненты связности
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
const int inf = (int)1e6;
using pii = pair<int,int>;
// функция для одномерного сжатия координат и сжатия отрезков:
auto buildTheGrid(auto &vec) {
    sort(all(vec));
    vec.erase(unique(all(vec)), vec.end());
    vector<pii> segs;
    for (int i = 0; i < isz(vec); i++) {
        int currX = vec[i];
        if (i - 1 >= 0) {
            int prevX = vec[i-1];
            if (prevX + 1 <= currX - 1)
                segs.emplace_back(prevX + 1, currX - 1);
        }
        segs.emplace_back(currX, currX);
    }
    return segs;
}
// нахождение позиции в отсортированном векторе:
int lowerBoundPos(const auto &vec, const auto &item) {
    return int(lower_bound(all(vec), item) - vec.begin());
}
main() {
    // читаем данные и запоминаем координаты:
    // Важно: умножаем координаты на 2, чтобы при сжатии учитывать узкое
    // пространство между соседними прямоугольниками
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tuple<int,int,int,int>> rects(n);
    vector<int> xx{-inf,inf}, yy{-inf,inf};
    for (auto &[x1,y1,x2,y2] : rects) {
        cin >> x1 >> y1 >> x2 >> y2;
        x1 *= 2, y1 *= 2, x2 *= 2, y2 *= 2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        xx.insert(xx.end(), {x1, x2});
        yy.insert(yy.end(), {y1, y2});
    }
    // строим сжатую сетку и рисуем карту из '.' и '#':
    auto segsX = buildTheGrid(xx);
    auto segsY = buildTheGrid(yy);
    vector a(isz(segsY), vector(isz(segsX), '.'));
    for (const auto &[x1,y1,x2,y2] : rects) {
        const int ix1 = lowerBoundPos(segsX, pii(x1, x1));
        const int ix2 = lowerBoundPos(segsX, pii(x2, x2));
        const int iy1 = lowerBoundPos(segsY, pii(y1, y1));
        const int iy2 = lowerBoundPos(segsY, pii(y2, y2));
        for (int i = ix1; i <= ix2; i++)
            a[iy1][i] = a[iy2][i] = '#';
        for (int i = iy1; i <= iy2; i++)
            a[i][ix1] = a[i][ix2] = '#';
    }
    // считаем количество компонент связности:
    vector used(isz(segsY), vector(isz(segsX), false));
    int answ{};
    for (int row = 0; row < isz(segsY); row++)
        for (int col = 0; col < isz(segsX); col++)
            if (a[row][col] == '.' && !used[row][col]) {
                function<void(int,int)> visit = [&](int r, int c) {
                    if (r < 0 || r >= isz(segsY)) return;
                    if (c < 0 || c >= isz(segsX)) return;
                    if (used[r][c] || a[r][c] == '#') return;
                    used[r][c] = 1;
                    visit(r-1, c);
                    visit(r+1, c);
                    visit(r, c-1);
                    visit(r, c+1);
                };
                visit(row, col);
                answ++;
            }
    cout << answ << endl;
}
