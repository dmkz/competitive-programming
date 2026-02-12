// геометрия, сканирующая прямая, сжатие координат, O(N^3)
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using namespace std;
using Rect = tuple<int,int,int,int>;
using pii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pii>;
using vvpii = vector<vpii>;
int lowpos(const auto &v, const auto &x) {
    return int(lower_bound(all(v), x) - v.begin());
}
auto compress(auto &x) {
    // сортируем координаты и удаляем повторы:
    sort(all(x));
    x.erase(unique(all(x)), x.end());
    // создаём отрезки в формате {r, l}
    vector<pii> res;
    for (int i = 0; i < isz(x); i++) {
        if (i > 0 && x[i-1] + 1 < x[i])
            res.emplace_back(x[i]-1, x[i-1]+1);
        res.emplace_back(x[i], x[i]);
    }
    return res;
}
main() {
    // читаем входные данные + сжимаем координаты:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<Rect> rects(n);
    vi xx, yy;
    for (auto &[x1,y1,x2,y2] : rects) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        y2--, x2--;
        xx.insert(xx.end(), {x1, x2});
        yy.insert(yy.end(), {y1, y2});
    }
    auto xSegs = compress(xx);
    auto ySegs = compress(yy);
    // создаём события прибавления и вычитания на отрезке:
    vvpii add(isz(xSegs)), rem(isz(xSegs));
    for (auto &[x1,y1,x2,y2] : rects) {
        // находим сжатые координаты:
        x1 = lowpos(xSegs, pii(x1, x1));
        x2 = lowpos(xSegs, pii(x2, x2));
        y1 = lowpos(ySegs, pii(y1, y1));
        y2 = lowpos(ySegs, pii(y2, y2));
        // создаём события:
        add[x1].emplace_back(y1, y2);
        rem[x2].emplace_back(y1, y2);
    }
    // сканируем слева-направо
    vi balance(isz(ySegs));
    auto update = [&](int y1, int y2, int delta) {
        for (int i = y1; i <= y2; i++)
            balance[i] += delta;
    };
    int64_t answer{};
    for (int x = 0; x < isz(xSegs); x++) {
        // добавляем новые отрезки:
        for (const auto &[y1, y2] : add[x])
            update(y1, y2, +1);
        // обновляем ответ:
        const int dx = xSegs[x].first - xSegs[x].second + 1;
        for (int i = 0; i < isz(balance); i++)
            if (balance[i])
                answer += dx * (ySegs[i].first - ySegs[i].second + 1LL);
        // удаляем старые отрезки:
        for (const auto &[y1, y2] : rem[x])
            update(y1, y2, -1);
    }
    cout << answer << endl;
}
