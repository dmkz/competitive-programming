#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
void reuniq(auto &v) { v.erase(std::unique(all(v)), v.end()); }
int getbit(int mask, int i) { return (mask >> i) & 1; }
// i-я окружность покрывает i-ю точку:
// (cx[i] - px[i])^2 + (cy[i] - py[i])^2 <= 1
// окружности i и j могут касаться но не пересекаются
// (cx[i] - cx[j])^2 + (cy[i] - cy[j])^2 >= 4
using ld = double;
using Pt = std::pair<ld,ld>;
using Real = ld;
using vi = std::vector<int>;
const Real EPS = 1e-9;

// Codeforces 600D: dmkozyrev solution
void for_intersect(Real x1, Real y1, Real r1, Real x2, Real y2, Real r2,
                   const auto &f) {
    Real dx = x2 - x1, dy = y2 - y1;
    Real d2 = dx*dx + dy*dy;
    Real d = std::sqrt(d2);

    if (d < EPS) {
        if (std::abs(r1 - r2) < EPS) return;
        return;
    }

    if (d > r1 + r2 + EPS) return;
    if (d < std::abs(r1 - r2) - EPS) return;

    Real a = (r1*r1 - r2*r2 + d*d) / (2*d);
    Real h2 = r1*r1 - a*a;
    if (h2 < 0 && h2 > -EPS) h2 = 0;
    if (h2 < 0) return;

    Real h = std::sqrt(h2);

    Real ux = dx / d, uy = dy / d;
    Real px = x1 + ux * a;
    Real py = y1 + uy * a;

    Real rx = -uy * h;
    Real ry =  ux * h;

    Pt p1{px + rx, py + ry};
    Pt p2{px - rx, py - ry};

    if (h < EPS) {
        f(p1);
        return;
    }
    f(p1); f(p2);
}

// Codeforces 600D: dmkozyrev solution
std::vector<Pt> intersect(Real x1, Real y1, Real r1, Real x2, Real y2, Real r2) {
    std::vector<Pt> result;
    for_intersect(x1, y1, r1, x2, y2, r2, [&](const Pt &p) {
        result.push_back(p);
    });
    return result;
}

auto intersect(Pt c1, Real r1, Pt c2, Real r2) {
    auto [x1,y1] = c1; auto [x2,y2] = c2;
    return intersect(x1,y1,r1,x2,y2,r2);
}


void for_intersect(Pt c1, Real r1, Pt c2, Real r2, const auto &f) {
    auto [x1,y1] = c1; auto [x2,y2] = c2;
    for_intersect(x1,y1,r1,x2,y2,r2,f);
}

ld dist2(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x2 - x1, dy = y2 - y1;
    return dx * dx + dy * dy;
}

ld dist2(const Pt &a, const Pt &b) {
    auto [x1,y1] = a; auto [x2,y2] = b;
    return dist2(x1,y1,x2,y2);
}

std::pair<bool, std::vector<Pt>> coverByASingleCircle(const auto &a) {
    // проверяем, можем ли покрыть одной окружностью
    // кандидаты на центр:
    // 1) сами точки;
    // 2) точки пересечения единичных окружностей
    static std::vector<Pt> candidates;
    candidates.assign(all(a));
    for (int i = 0; i < isz(a); i++)
        for (int j = i+1; j < isz(a); j++)
            for (auto p : intersect(a[i], 1, a[j], 1))
                candidates.push_back(p);
    std::vector<Pt> result;
    for (auto c : candidates) {
        bool ok = true;
        for (auto ai : a)
            ok &= (dist2(c, ai) <= 1 + EPS);
        if (ok)
            result.push_back(c);
    }
    return {result.size() > 0u, result};
}
// выбираем подмножество точек:
std::vector<Pt> select(std::vector<Pt> a, const vi &indexes) {
    assert(std::is_sorted(all(indexes)));
    int j = 0;
    for (int i : indexes)
        a[j++] = a[i];
    a.resize(j);
    return a;
}
std::mt19937 gen;
const auto submask = [](){
    // для каждой маски и единичного бита нужны её подмаски
    std::vector res(1 << 10, std::vector(10, vi{}));
    for (int mask = 0; mask < (1 << 10); mask++)
        for (int i = 0; i < 10; i++) {
            for (int sub = 0; sub < (1 << 10); sub++) {
                if ((mask & sub) == sub)
                    if (getbit(sub, i))
                        res[mask][i].push_back(sub);
            }
            std::stable_sort(all(res[mask][i]), [](int a, int b) {
                return __builtin_popcount(a) > __builtin_popcount(b);
            });
        }
    return res;
}();
void solve() {
    // читаем точки, сортируем и удаляем повторы:
    int n; std::cin >> n;
    std::vector<Pt> a(n);
    for (auto &[x,y] : a)
        std::cin >> x >> y;
    std::sort(all(a));
    reuniq(a);
    n = isz(a);
    // переставляем точки
    //std::shuffle(all(a), gen);
    // найдём множества точек покрываемые одной окружностью:
    
    std::vector<std::pair<bool, std::vector<Pt>>> canBeCovered(1 << n);
    for (int mask = 1; mask < (1 << n); mask++) {
        vi indexes;
        for (int i = 0; i < n; i++)
            if (getbit(mask, i))
                indexes.push_back(i);
        canBeCovered[mask] = coverByASingleCircle(select(a, indexes));
    }
    // перебор:
    std::vector<Pt> answer, circles;
    std::function<void(int)> dfs = [&](int empty) {
        if (empty == 0) {
            // все точки покрыты, нашли ответ
            answer = circles;
            return;
        }
        // находим первую непокрытую точку и пытаемся покрыть как можно больше
        // вместе с ней
        int curr = std::__lg(empty);
        assert(getbit(empty, curr));
        vi indexes;
        std::vector<Pt> candidates;
        for (int mask : submask[empty][curr]) {
            if (!canBeCovered[mask].first) continue;
            if (answer.size()) break;
            indexes.clear();
            for (int i = 0; i < n; i++)
                if (getbit(mask, i))
                    indexes.push_back(i);
            candidates = canBeCovered[mask].second;
            for (auto c : circles)
                for (auto i : indexes)
                    for_intersect(c, 2, a[i], 1, [&](const Pt &p){
                        candidates.push_back(p);
                    });
            std::sort(all(candidates));
            reuniq(candidates);
            for (auto cand : candidates) {
                bool ok = true;
                for (auto c : circles)
                    ok &= (dist2(cand, c) >= 4 - EPS);
                for (auto i : indexes)
                    ok &= (dist2(cand, a[i]) <= 1 + EPS);
                if (ok) {
                    circles.push_back(cand);
                    if (answer.empty()) dfs(empty ^ mask);
                    circles.pop_back();
                }
            }
        }
    };
    dfs((1 << n) - 1);
    if (answer.size()) {
        std::cout << "YES\n";
        std::cout << answer.size() << "\n";
        for (auto [x,y] : answer)
            std::cout << x << ' ' << y << '\n';
    } else {
        std::cout << "NO\n";
    }
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
