#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
using namespace std;
using ld = long double;
using ll = long long;
using pldi = pair<ld, int>;
using pii = pair<int, int>;
using pldld = pair<ld, ld>;
const ld pi = acosl(-1);

const int shift = (int)1e9+1;
int main() {
    // читаем точки
    int n, m, k; cin >> n >> m >> k;
    vector<pair<int,int>> points(n);
    pldi maxAngle(-pi,0), minAngle(pi, 0);
    for (int i = 0; i < n; i++) {
        auto &[x, y] = points[i];
        cin >> x >> y;
        x += shift, y += shift; // сдвигаем в первую четверть
        setmin(minAngle, pldi(atan2l(y,x), i));
        setmax(maxAngle, pldi(atan2l(y,x), i));
    }
    // все точки выпуклой оболочки лежат между minAngle и maxAngle в I четверти
    // всех от минимального угла до максимального вставляем в верхний сет
    // остальных - в нижний сет
    set<pldi> lower = {minAngle, maxAngle}, upper = {minAngle, maxAngle};
    for (int i = minAngle.second; i != maxAngle.second; (i+=1)%=n) {
        const auto &[x, y] = points[i];
        upper.insert(pldi(atan2l(y,x), i));
    }
    for (int i = maxAngle.second; i != minAngle.second; (i+=1)%=n) {
        const auto &[x, y] = points[i];
        lower.insert(pldi(atan2l(y,x), i));
    }
    // отвечаем на запросы:
    while(m--) {
        int x, y; cin >> x >> y;
        x += shift, y += shift; // сдвиг в первую четверть
        auto angle = atan2l(y,x);
        if (angle < minAngle.first || angle > maxAngle.first) {
            continue; // точно не лежит внутри
        }
        // алгоритм проверки следующий:
        // выбираем точку обзора. Например: (0, 0)
        // смотрим из неё в направлении точки из запроса
        // если мы пересекаем нижнюю часть оболочки, затем видим точку,
        // а затем пересекаем верхнюю часть оболочки, то всё в порядке
        
        static vector<pldld> results;
        results.clear();
        // функция для нахождения пересечения:
        auto intersect = [&](int Bx, int By, pldi fi, pldi se) {
            // нужно найти точку пересечения двух отрезков
            // A + (B - A) * t == C + (D - C) * q
            // (B - A) * t - (D - C) * q == C - A
            pii A{0,0}, B{Bx, By}, C = points[fi.second], D = points[se.second];
            // (B.x - A.x) * t + (C.x - D.x) * q == C.x - A.x
            // (B.y - A.y) * t + (C.y - D.y) * q == C.y - A.y
            auto [Ax,Ay] = A;
            //auto [Bx,By] = B;
            auto [Cx,Cy] = C;
            auto [Dx,Dy] = D;
            ll det = (Bx - Ax)*1LL*(Cy - Dy)-(Cx - Dx)*1LL*(By - Ay);
            ll t = (Cx - Ax)*1LL*(Cy - Dy)-(Cx - Dx)*1LL*(Cy - Ay);
            //ll q = (Bx - Ax)*1LL*(Cy - Ay)-(Cx - Ax)*1LL*(By - Ay);
            if (det == 0) {
                // особый случай: три точки лежат на одной прямой
                // можем сразу сказать ответ, если наша лежит между двумя другими
                results = {B,C,D};
                return false;
            }
            ld cx = Ax + (Bx - Ax) * (t * 1.0L / det);
            ld cy = Ay + (By - Ay) * (t * 1.0L / det);
            results.push_back({cx,cy});
            return true;
        };
        // ищем бинпоиском пересечение с каждой из половинок выпуклой оболочки:
        results = {{x,y}};
        for (auto half : {&lower,&upper}) {
            auto it = half->lower_bound(pldi(angle,0));
            pldi fi, se;
            if (it == half->begin()) {
                fi = *it;
                se = *next(it);
            } else {
                fi = *prev(it);
                se = *it;
            }
            if (!intersect(x,y,fi,se))
                break;
        }
        std::sort(all(results));
        k -= (results.size() == 3u && results[1] == pldld(x,y));
    }
    std::cout << (k <= 0 ? "YES\n" : "NO\n");
    return 0;
}