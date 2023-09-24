#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()

using namespace std;
const int MAX = (int)1e8;
using t4i = tuple<int,int,int,int>;
using vt4i = vector<t4i>;
using pii = pair<int,int>;
using vpii = vector<pii>;

t4i createLineBetween(pii fi, pii se) {
    // проводим прямую через полусумму точек посередине
    auto [x1,y1] = fi;
    auto [x2,y2] = se;
    int xb = x1-1;
    int yb = MAX+1;
    // (xb,yb) + k * ((x1+x2)/2 - xb, (y1+y2)/2 - yb)
    // возьмём k = 2
    // (xb,yb) + ((x1+x2) - 2 * xb, (y1+y2) - 2 * yb)
    int xa = xb + (x1+x2) - 2 * xb;
    int ya = yb + (y1+y2) - 2 * yb;
    return {xa,ya,xb,yb};
}

vt4i solve(int n, vpii a) {
    // будем вставлять точки в обратном порядке:
    reverse(a.begin(), a.end());
    // храним два множества из точек:
    set<pii> lower, upper;
    // lower - нижняя половина в посорченном порядке
    // upper - верхняя половина в посорченном порядке
    auto insert = [&](pii point) {
        // вставляем либо в верхнюю половину, либо в нижнюю
        if (isz(upper) && point >= *upper.begin()) {
            upper.insert(point);
        } else
            lower.insert(point);
        // перекладываем из нижней в верхнюю пока размеры не сравняются
        while (isz(lower) > isz(upper)) {
            auto last = prev(lower.end());
            upper.insert(*last);
            lower.erase(last);
        }
        // перекладываем из верхней в нижнюю пока размеры не сравняются
        while (isz(upper) - isz(lower) > 1) {
            lower.insert(*upper.begin());
            upper.erase(upper.begin());
        }
        assert(isz(upper) >= isz(lower));
    };
    vt4i answ;
    for (int i = 0; i < n; i++) {
        insert(a[i]);
        if (i % 2 == 0) {
            // число точек нечётно, проводим через центральную
            assert(isz(upper) > isz(lower));
            answ.push_back(createLineBetween(*upper.begin(), *upper.begin()));
        } else {
            // число точек чётно, проводим через полусумму центральных
            assert(isz(upper) == isz(lower));
            answ.push_back(createLineBetween(*lower.rbegin(), *upper.begin()));
        }
    }
    reverse(all(answ));
    return answ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        vector<pair<int,int>> a(n);
        for (auto &[x,y] : a)
            cin >> x >> y;
        auto res = solve(n, a);
        for (auto &[xa,ya,xb,yb] : res)
            cout << xa << ' ' << ya << ' ' << xb << ' ' << yb << "\n";
    }
}