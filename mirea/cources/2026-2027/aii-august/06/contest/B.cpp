#include <bits/stdc++.h>
using namespace std;
// структура данных для хранения прямоугольника:
struct Rect {
    int xMin, yMin, xMax, yMax;
    Rect(int x1, int y1, int x2, int y2)
        : xMin(x1), yMin(y1), xMax(x2), yMax(y2) {}
    int64_t square() const {
        return int64_t(max(0, xMax-xMin))*max(0, yMax-yMin);
    }
};
// пересечение двух прямоугольников:
Rect intersect(Rect a, Rect b) {
    return Rect(max(a.xMin, b.xMin), max(a.yMin, b.yMin),
                min(a.xMax, b.xMax), min(a.yMax, b.yMax));
}
// решение задачи:
const int inf = (int)1e9+7;
void solve() {
    // читаем прямоугольники:
    int n; cin >> n;
    vector<int> x1(1+n+1,-inf), y1(1+n+1,-inf),
                x2(1+n+1,+inf), y2(1+n+1,+inf);
    for (int i = 1; i <= n; i++) cin >> x1[i];
    for (int i = 1; i <= n; i++) cin >> y1[i];
    for (int i = 1; i <= n; i++) cin >> x2[i];
    for (int i = 1; i <= n; i++) cin >> y2[i];
    // Считаем пересечение прямоугольников на каждом префиксе:
    vector<Rect> pref(1+n+1, Rect(-inf,-inf,+inf,+inf));
    for (int i = 1; i <= n; i++)
        pref[i] = intersect(pref[i-1], Rect(x1[i], y1[i], x2[i], y2[i]));
    // Считаем пересечение прямоугольников на каждом суффиксе:
    vector<Rect> suff(1+n+1, Rect(-inf,-inf,+inf,+inf));
    for (int i = n; i >= 1; i--)
        suff[i] = intersect(suff[i+1], Rect(x1[i], y1[i], x2[i], y2[i]));
    // Находим максимальную площадь пересечения всех прямоугольников, исключая i-й:
    int64_t bestS = -1, bestI = -1;
    for (int i = 1; i <= n; i++) {
        int64_t si = intersect(pref[i-1], suff[i+1]).square();
        if (bestS < si) bestS = si, bestI = i;
    }
    cout << bestI << ' ' << bestS << '\n';
}   
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
