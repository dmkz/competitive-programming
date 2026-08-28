#include <bits/stdc++.h>
using namespace std;
// структура для хранения точки:
struct Point {
    int x, y;
};
// разность двух точек:
Point operator-(const Point &a, const Point &b) {
    return {a.x - b.x, a.y - b.y};
}
// векторное произведение:
int64_t cross(Point a, Point b) {
    return a.x * 1LL * b.y - a.y * 1LL * b.x;
}
// решение задачи:
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (auto &it : x) cin >> it;
    for (auto &it : y) cin >> it;
    // сначала отметим сами пики:
    vector<bool> isPeak(n, false);
    int cntPeaks = 0;
    for (int i = 1; i + 1 < n; i++) {
        isPeak[i] = (y[i] > max(y[i-1], y[i+1]));
        cntPeaks += (isPeak[i]);
    }
    // теперь для каждого горного пика посчитаем, сколько пиков мы с него увидим
    vector<int> answ(n);
    for (int i = 1; i + 1 < n; i++) {
        if (!isPeak[i]) continue;
        Point pi = {x[i], y[i]};
        {   // считаем в правую сторону: храним точку, которая образует максимальный угол
            // мы видим новый горный пик, если прямая от текущей точки до него не пересекает
            // ни одну из предыдущих точек. Это означает новый максимальный угол, ведь все
            // остальные находятся ниже.
            // ОЧЕНЬ ВАЖНО: максимум храним среди всех точек, а не только среди пиков
            int m = i+1;
            for (int r = i+2; r < n; r++) {
                Point currVec = Point{x[r], y[r]} - pi;
                Point bestVec = Point{x[m], y[m]} - pi;
                // Если самый лучший вектор находится под текущим:
                if (cross(bestVec, currVec) > 0) {
                    // новый максимум
                    answ[i] += isPeak[r];
                    m = r;
                }
            }
        }
        // аналогично считаем в левую сторону:
        int m = i-1;
        for (int l = i-2; l >= 0; l--) {
            Point currVec = Point{x[l], y[l]} - pi;
            Point bestVec = Point{x[m], y[m]} - pi;
            // если самый лучший вектор находится под текущим:
            if (cross(bestVec, currVec) < 0) {
                // новый минимум
                answ[i] += isPeak[l];
                m = l;
            }
        }
    }
    // выводим ответы:
    cout << cntPeaks << '\n';
    for (int i = 0; i < n; i++)
        if (isPeak[i])
            cout << i+1 << ' ' << answ[i] << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
