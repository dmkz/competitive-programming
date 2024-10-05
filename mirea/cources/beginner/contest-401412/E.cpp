#include <bits/stdc++.h>
using namespace std;

const int MAX_COORD = +(int)1e9;
const int MIN_COORD = -(int)1e9;

// структура данных для хранения прямоугольника:
struct Rect {
    int xMin, yMin, xMax, yMax;
};

const Rect MAX_RECT = {MIN_COORD, MIN_COORD, MAX_COORD, MAX_COORD};

// функция пересечения двух прямоугольников:
Rect intersect(Rect A, Rect B) {
    int xMin = max(A.xMin, B.xMin);
    int yMin = max(A.yMin, B.yMin);
    int xMax = min(A.xMax, B.xMax);
    int yMax = min(A.yMax, B.yMax);
    return {xMin, yMin, xMax, yMax};
}

int main() {
    // читаем данные, будем использовать 1 индексацию!
    // чтобы не выходить за пределы при pref[i-1] и suff[i+1]
    int n; cin >> n;
    vector<Rect> rectangles(1 + n + 1, MAX_RECT);
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rectangles[i] = {x1, y1, x2, y2};
    }
    // пересечение прямоугольников на каждом префиксе:
    // pref[i] = пересечение(0, 1, 2, ..., i)
    vector<Rect> pref(1+n+1, MAX_RECT);
    for (int i = 1; i <= n; i++)
        pref[i] = intersect(pref[i-1], rectangles[i]);
    // пересечение прямоугольников на каждом суффиксе:
    // suff[i] = пересечение(i, i+1, i+2, ..., n-1)
    vector<Rect> suff(1+n+1, MAX_RECT);
    for (int i = n; i >= 1; i--)
        suff[i] = intersect(suff[i+1], rectangles[i]);
    // теперь переберём номер прямоугольника, который выкидываем, и посмотрим,
    // что получится без него:
    for (int i = 1; i <= n; i++) {
        Rect res = intersect(pref[i-1], suff[i+1]);
        if (res.xMin <= res.xMax && res.yMin <= res.yMax) {
            cout << res.xMin << ' ' << res.yMin << '\n';
            return 0;
        }
    }
    assert(false && "This must never happen!!!");
}