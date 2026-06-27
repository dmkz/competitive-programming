// полярный угол, ориентированный угол, эквивалентность, минимальный циклический сдвиг
// Задача: I, Вердикт: OK, Время: 2.703s, Память: 15.73Mb
#include <bits/stdc++.h>
#include <cassert>

#define int ll

#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using ld = long double;
using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using vpii = std::vector<pii>;
using vpll = std::vector<pll>;
using vd = std::vector<ld>;
using vi = std::vector<int>;

ll cross(pii a, pii b) {
    return a.first * b.second - a.second * b.first;
}

ll dot(pii a, pii b) {
    return a.first * b.first + a.second * b.second;
}

pll getIntAngle(pii a, pii b) {
    ll x = cross(a, b);
    ll y = dot(a, b);
    ll g = std::gcd(std::abs(x), std::abs(y));
    return {x / g, y / g};
}

pll getIntScale(pii a, pii b) {
    ll x = dot(a, a);
    ll y = dot(b, b);
    ll g = std::gcd(std::abs(x), std::abs(y));
    return {x / g, y / g};
}

ll norm2(pii a) {
    return ({auto [x, y] = a; x * 1LL * x + y * 1LL * y;});
}

struct Parent {
    int k{};
    std::vector<std::pair<pll, pll>> data;
    Parent(int k_, const auto &alpha, const auto &gamma)
        : k(k_), data(alpha.size())
    {
        for (int i = 0; i < isz(data); i++)
            data[i] = {alpha[i], gamma[i]};
    }
    void normalize() {
        auto a = data;
        a.insert(a.end(), all(data));
        int minI = 0;
        for (int i = 0; i < isz(data); i++) {
            int res = 0;
            for (int j = 0; j < isz(data); j++) {
                if (a[minI + j] < a[i + j]) {
                    res = -1;
                    break;
                }
                if (a[minI + j] > a[i + j]) {
                    res = +1;
                    break;
                }
            }
            if (res > 0)
                minI = i;
        }
        for (int i = 0; i < isz(data); i++)
            data[i] = a[minI + i];
    }
};
bool operator<(const Parent &a, const Parent &b) {
    if (a.k < b.k) return true;
    if (a.k > b.k) return false;
    return a.data < b.data;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, p; std::cin >> n >> p;
    vi where(n,-1);
    std::map<Parent, int> parents;
    std::map<int, vi> subsets;
    for (int pointId = 0; pointId < n; pointId++) {
        // читаем точки + считаем центр масс:
        vpii points(p);
        int sx = 0, sy = 0;
        for (auto &[x, y] : points) {
            std::cin >> x >> y;
            sx += x, sy += y;
        }
        // строим векторы относительно центра масс:
        for (auto &[x, y] : points) {
            x = p * x - sx;
            y = p * y - sy;
        }
        // удаляем нулевые векторы, считая их количество:
        int k = 0;
        for (int j = 0; j < isz(points); j++) {
            if (points[j] == pii(0, 0))
                continue;
            points[k++] = points[j];
        }
        points.resize(k);
        // сортируем по полярному углу:
        std::sort(all(points), [&](pii a, pii b){
            auto [ax, ay] = a;
            auto [bx, by] = b;
            ld a1 = std::atan2l(ay, ax);
            ld a2 = std::atan2l(by, bx);
            ll lenA = norm2(a);
            ll lenB = norm2(b);
            if (!(a1 != a2)) return lenA < lenB;
            return a1 < a2;
        });
        // строим последовательность ориентированных углов (alpha) и
        // коэффициентов отношения длин (gamma) в целых числах для всех
        // пар соседних векторов (на окружности)
        vpll alpha(isz(points)), gamma(isz(points));
        for (int i = 0; i < isz(points); i++) {
            int j = (i+1) % isz(points);
            alpha[i] = getIntAngle(points[j], points[i]);
            gamma[i] = getIntScale(points[j], points[i]);
        }
        // Определяем уникальный класс текущего множества:
        Parent par(k, alpha, gamma);
        par.normalize();
        int parInd = parents.insert({par, isz(parents)}).first->second;
        // нашли предка: добавляем себя в множество эквивалентных ему:
        where[pointId] = parInd;
        subsets[parInd].push_back(pointId);
    }
    // Вывод ответа:
    for (int i = 0; i < n; i++) {
        int parId = where[i];
        const auto &vec = subsets[parId];
        std::cout << isz(vec)-1;
        for (auto it : vec)
            if (it != i)
                std::cout << ' ' << it+1;
        std::cout << "\n";
    }
}
