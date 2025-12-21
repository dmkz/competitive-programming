#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ld = double;
using ll = long long;
using Pt = std::pair<ld, ld>;
const ld EPS = 1e-9, SQRT3 = std::sqrt(ld(3));
// ищем покрытие кругами в гексагональной сетке
bool findCoverCenters(const std::vector<Pt> &p,
                      ld shiftX, ld shiftY, std::vector<Pt> &centers)
{
    centers.clear();
    for (const auto &[x, y] : p) {
        bool found = false;
        Pt currCircle{0, 0};
        // y = shiftY + j * sqrt(3)
        ll j0 = (ll)std::round((y - shiftY) / SQRT3); // примерно по оси Oy
        for (ll j = j0-2; j <= j0+2 && !found; j++) {
            ld cy = shiftY + (ld)j * SQRT3;
            ld dy2 = (y - cy) * (y - cy);
            if (dy2 > 1.0 + EPS)
                continue;
            int parity = (int)(j & 1LL);
            ld xShifted = x - shiftX - (ld)parity;
            ll i0 = (ll)std::round(xShifted / 2.0); // примерно по оси Оx
            for (ll i = i0-2; i <= i0+2; i++) { // найдём точное решение
                ld cx = shiftX + (ld)parity + 2.0*(ld)i;
                // (cx, cy) - центр текущей окружности на нашей
                // гексагональной сетке
                ld d2 = (x - cx) * (x - cx) + dy2;
                if (d2 <= 1.0 + EPS) {
                    currCircle = {cx, cy};
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
        centers.push_back(currCircle);
    }
    std::sort(all(centers));
    centers.erase(std::unique(all(centers)), centers.end());
    return true;
}
const uint64_t seed = 3101199815021996ULL;
std::mt19937_64 gen(seed);
std::uniform_real_distribution<ld> shiftX(0, 2), shiftY(0, SQRT3);
void solve() {
    int n; std::cin >> n;
    std::vector<Pt> p(n);
    for (auto &[x, y] : p)
        std::cin >> x >> y;
    // будем случайным образом двигать гексагональную сетку из кругов
    // пока не получим такой сдвиг, при котором ни одна из точек не попадёт
    // в пространство между кругами.
    std::vector<Pt> centers;
    while (!findCoverCenters(p, shiftX(gen), shiftY(gen), centers));
    // выводим ответ. он всегда существует
    std::cout << "YES\n";
    std::cout << centers.size() << "\n";
    for (const auto &[x,y] : centers)
        std::cout << x << " " << y << "\n";
}
main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}