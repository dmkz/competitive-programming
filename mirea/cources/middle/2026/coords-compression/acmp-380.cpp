// сжатие прямоугольников, площадь объединения прямоугольников
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
void sortAndUnique(auto &vec) {
    sort(all(vec));
    vec.erase(unique(all(vec)), vec.end());
}
main() {
    // читаем данные и запоминаем координаты:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tuple<int,int,int,int>> rects(n);
    vector<int> xx, yy;
    for (auto &[x1,y1,x2,y2] : rects) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        xx.insert(xx.end(), {x1, x2});
        yy.insert(yy.end(), {y1, y2});
    }
    // строим сжатую сетку и считаем ответ:
    sortAndUnique(xx);
    sortAndUnique(yy);
    int64_t answ{};
    for (int ix = 0; ix + 1 < isz(xx); ix++) {
        for (int iy = 0; iy + 1 < isz(yy); iy++) {
            // считаем, во сколько прямоугольников входит ячейка (ix, iy):
            int cnt = 0;
            for (const auto &[x1,y1,x2,y2] : rects)
                cnt += (
                    x1 <= xx[ix] && xx[ix+1] <= x2 &&
                    y1 <= yy[iy] && yy[iy+1] <= y2);
            // прибавляем её к ответу, если входит в хотя бы один:
            if (cnt > 0)
                answ += (xx[ix+1] - xx[ix]) * 1LL * (yy[iy+1] - yy[iy]);
        }
    }
    cout << answ << "\n";
}
