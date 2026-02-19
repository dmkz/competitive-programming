// геометрия, бинарный поиск, пересечение прямых, расстояние от точки до прямой
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
ld det(ll a, ll b, ll c, ll d) {
    return a * d - b * c;
}
struct Line {
    ll A{}, B{}, C{};
    Line(ll xc, ll yc, ll vx, ll vy)
    {
        // уравнение прямой, проходящей через точку (xc, yc) в направлении (vx, vy)
        // (x - xc) * (-vy) + (y - yc) * vx = 0
        // (-vy) * x + (vx) * y + xc * vy - yc * vx = 0
        A = -vy, B = vx, C = xc * 1LL * vy - yc * 1LL * vx;
    }
    ll operator()(ll x, ll y) const {
        return A * x + B * y + C;
    }
    ll operator()(pll pt) const {
        return (*this)(pt.first, pt.second);
    }
    ld dist(pll pt) const {
        ll a = (*this)(pt);
        ld b = std::sqrt(ld(A*A+B*B));
        return std::abs(a) / b;
    }
    ld dist(ll x, ll y) const {
        return dist(pll(x, y));
    }
    pdd intersect(const Line &L) {
        // пересечение двух прямых
        // A * x + B * y + C == 0
        ld a = det(-C, -L.C, B, L.B);
        ld b = det(A, L.A, -C, -L.C);
        ld q = det(A, B, L.A, L.B);
        return {a/q, b/q};
    }
};
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем все данные и преобразуем их в метры:
    int r, n, q; cin >> r >> n >> q;
    int xc, yc; cin >> xc >> yc;
    xc *= 1000, yc *= 1000;
    int vx, vy;
    cin >> vx >> vy;
    vx *= 1000, vy *= 1000;
    // Правая граница траектории:
    Line line(xc, yc, vx, vy);
    // начинаем считать ответ для каждого ряда:
    ll answ{};
    for (int i = 0; i < n; i++) {
        int L = -i * 1000;
        Line curr(-i*1000, i*1000, 1, 0);
        auto [x, _] = curr.intersect(line);
        // ближайшие слева и справа к точке x:
        // L + 2000 * k <= x
        // L + 2000 * k >= x
        ll leftK = (ll)std::floor((x - L) / 2000.0L);
        ll rightK = (ll)std::ceil((x - L) / 2000.0L);
        // бинарным поиском находим левую точку:
        ll left = [&]() -> ll{
            ll low = -1, high = leftK+1;
            while (high - low > 1) {
                ll mid = (low+high) / 2;
                if (line.dist(L + mid * 2000, i * 1000) > q + r)
                    low = mid;
                else
                    high = mid;
            }
            return low;
        }();
        // бинарным поиском находим правую точку:
        ll right = [&]() -> ll {
            ll low = rightK-1, high = i+1;
            while (high - low > 1) {
                ll mid = (low + high) / 2;
                if (line.dist(L+mid*2000,i*1000) > q + r)
                    high = mid;
                else
                    low = mid;
            }
            return high;
        }();
        // увеличиваем ответ: все точки от left+1 до right-1:
        answ += std::max<ll>(0, right - left - 1);
    }
    std::cout << answ << std::endl;
}
