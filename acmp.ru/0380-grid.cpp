// двумерное сжатие координат, сетка, площадь прямоугольников
#include <bits/stdc++.h>
using namespace std;
struct Rect { int x1, y1, x2, y2; };
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем прямоугольники и сжимаем координаты:
    int n; cin >> n;
    vector<Rect> rects(n);
    vector<int> xx, yy;
    for (auto &[x1, y1, x2, y2] : rects) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        xx.insert(xx.end(), {x1, x2});
        yy.insert(yy.end(), {y1, y2});
    }
    // сортируем и удаляем повторы:
    for (auto vec : {&xx, &yy}) {
        sort(vec->begin(), vec->end());
        vec->erase(unique(vec->begin(), vec->end()), vec->end());
    }
    // строим сетку + отмечаем клетки:
    vector grid(yy.size()-1, vector(xx.size()-1, 0));
    for (const auto &[x1, y1, x2, y2] : rects) {
        int i1 = int(lower_bound(yy.begin(), yy.end(), y1) - yy.begin());
        int i2 = int(lower_bound(yy.begin(), yy.end(), y2) - yy.begin());
        int j1 = int(lower_bound(xx.begin(), xx.end(), x1) - xx.begin());
        int j2 = int(lower_bound(xx.begin(), xx.end(), x2) - xx.begin());
        for (int i = i1; i < i2; i++)
            for (int j = j1; j < j2; j++)
                grid[i][j]++;
    }
    // считаем ответ:
    int64_t answ{};
    for (int i = 0; i + 1 < (int)yy.size(); i++)
        for (int j = 0; j + 1 < (int)xx.size(); j++)
            if (grid[i][j])
                answ += (yy[i+1] - yy[i]) * 1LL * (xx[j+1] - xx[j]);
    cout << answ << endl;
}
