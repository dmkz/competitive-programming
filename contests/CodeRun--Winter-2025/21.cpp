#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ld = double;
using ll = long long;
using Pt = std::pair<ld, ld>;
ld dist2(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x1 - x2, dy = y1 - y2;
    return dx * dx + dy * dy;
}
ld dist2(const Pt &a, const Pt &b) {
    auto [x1, y1] = a; auto [x2, y2] = b;
    return dist2(x1, y1, x2, y2);
}
const ld EPS = 1e-9;
const ld SQRT3 = std::sqrt(ld(3));
ld modPos(ld a, ld m) {
    a = fmod(a, m);
    if (a < 0)
        a += m;
    return a;
}
static inline uint64_t splitmix64(uint64_t &x) {
    x += 0x9e3779b97f4a7c15ULL;
    uint64_t z = x;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}
// ищем покрытие кругами в гексагональной сетке
bool findCoverCenters(const std::vector<Pt> &p,
                      ld tx, ld ty, std::vector<Pt> &centers)
{
    centers.clear();
    tx = modPos(tx, 2.0);
    ty = modPos(ty, SQRT3);
    for (const auto &[x, y] : p) {
        bool found = false;
        Pt best{0, 0};
        // jj * sqrt(3) + ty = y
        ld jj = (y - ty) / SQRT3;
        ll j0 = (ll)std::round(jj); // примерно по оси Oy
        for (ll j = j0-2; j <= j0+2 && !found; j++) {
            ld cy = ty + (ld)j * SQRT3;
            ld dy = y - cy;
            ld dy2 = dy * dy;
            if (dy2 > 1.0 + EPS)
                continue;
            int par = (int)(j & 1LL);
            ld xrel = x - tx - (ld)par;
            ll i0 = (ll)std::round(xrel / 2.0); // примерно по оси Оx
            for (ll i = i0-2; i <= i0+2; i++) { // найдём точное решение
                ld cx = tx + (ld)par + 2.0*(ld)i;
                // (cx, cy) - центр текущей окружности на нашей
                // гексагональной сетке
                ld d2 = (x - cx) * (x - cx) + dy2;
                if (d2 <= 1.0 + EPS) {
                    best = {cx, cy};
                    found = true;
                    break;
                }
            }
        }
        if (!found)
            return false;
        bool duplicated = false;
        for (auto &c: centers) {
            if (dist2(c, best) <= EPS*EPS) {
                duplicated = true;
                break;
            }
        }
        if (!duplicated)
            centers.push_back(best);
        if (isz(centers) > isz(p))
            return false;
    }
    return true;
}
uint64_t seed = 3101199815021996ULL;
void solve() {
    int n; std::cin >> n;
    std::vector<Pt> p(n);
    for (auto &[x, y] : p)
        std::cin >> x >> y;
    std::vector<Pt> centers, answer;
    bool ok = false;
    std::vector<Pt> shifts;
    shifts.reserve(512);
    shifts.push_back({0.0, 0.0});
    shifts.push_back({1.0, 0.0});
    shifts.push_back({0.0, SQRT3*0.5});
    shifts.push_back({1.0, SQRT3*0.5});
    for (auto &[x,y] : p) {
        ld tx = modPos(x, 2.0);
        ld ty = modPos(y, SQRT3);
        shifts.push_back({tx, ty});
    }
    for (int it = 0; it < 400; it++) {
        uint64_t a = splitmix64(seed);
        uint64_t b = splitmix64(seed);
        ld tx = (ld)(a >> 11) * (1.0 / (ld)(1ULL << 53)) * 2.0;
        ld ty = (ld)(b >> 11) * (1.0 / (ld)(1ULL << 53)) * SQRT3;
        shifts.emplace_back(tx, ty);
    }
    for (const auto &[tx, ty] : shifts) {
        if (findCoverCenters(p, tx, ty, centers)) {
            answer = centers;
            ok = true;
            break;
        }
    }
    if (ok) {
        std::cout << "YES\n";
        std::cout << answer.size() << "\n";
        for (const auto &[x,y] : answer)
            std::cout << x << " " << y << "\n";
    } else
        std::cout << "NO\n";
}
main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
