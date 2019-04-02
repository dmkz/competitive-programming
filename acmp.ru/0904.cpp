/*
    Задача: 904. Crimsonland
    
    Решение: геометрия, бинарный поиск, перебор, O(n * log(n) * 360 / a)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
typedef long double ld;
const ld PI = std::acos(ld(-1));
const ld EPS = 1e-14L;
struct Vec {
    ld x, y, angle;
};
ld dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}
ld norm(const Vec& a) {
    return std::sqrt(dot(a,a));
}
bool less(ld a, ld b) {
    return a < b * (1 + EPS);
}
int solve(ld angle, std::vector<Vec> arr) {
    for (auto &it : arr) {
        it.angle = std::atan2(it.y,it.x);
    }
    std::stable_sort(all(arr), [&](const Vec& a, const Vec& b) {
        return a.angle < b.angle;
    });
    const int n = isz(arr);
    for (int i = 0; i < n; ++i) {
        arr.push_back(arr[i]);
        arr.back().angle += 2 * PI;
    }
    auto subtask = [&](int id) {
        int limit = id + n, answ = 0;
        while (id < limit) {
            answ++;
            int low = id, high = isz(arr);
            while (high - low > 1) {
                int mid = (low + high) / 2;
                if (less(arr[mid].angle - arr[id].angle, angle)) {
                    low = mid;
                } else { high = mid; }
            }
            id = high;
        }
        return answ;
    };
    int answ = n;
    for (int i = 0; i < n; ++i) {
        answ = std::min(answ, subtask(i));
    }
    return answ;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, a; std::cin >> n >> a; ) {
        Vec p; std::cin >> p.x >> p.y;
        std::vector<Vec> arr(n);
        for (auto &it : arr) {
            std::cin >> it.x >> it.y;
            it.x -= p.x, it.y -= p.y;
        }
        std::cout << solve(a * PI / 180, arr) << std::endl;
    }
    return 0;
}