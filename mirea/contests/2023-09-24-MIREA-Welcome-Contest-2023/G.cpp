// submit: 2
#include <bits/stdc++.h>
using namespace std;
const int MAX = (int)1e8;

using t4i = tuple<int,int,int,int>;
using pii = pair<int,int>;

t4i createLineBetween(pii fi, pii se) {
    // проводим прямую через полусумму точек посередине
    auto [x1,y1] = fi;
    auto [x2,y2] = se;
    // проводим почти вертикальную линию, уходящую в бесконечность
    int xb = x1-1;
    int yb = MAX+1;
    // (xb,yb) + k * ((x1+x2)/2 - xb, (y1+y2)/2 - yb)
    // возьмём k = 2
    // (xb,yb) + ((x1+x2) - 2 * xb, (y1+y2) - 2 * yb)
    int xa = xb + (x1+x2) - 2 * xb;
    int ya = yb + (y1+y2) - 2 * yb;
    return {xa,ya,xb,yb};
}

t4i solve(int n, vector<pii> a) {
    sort(a.begin(), a.end());
    if (n % 2 == 0) return createLineBetween(a[n/2-1],a[n/2]);
    else return createLineBetween(a[n/2],a[n/2]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; cin >> n;
        vector<pii> a(n);
        for (auto &[x,y] : a)
            cin >> x >> y;
        auto [xa,ya,xb,yb] = solve(n, a);
        cout << xa << ' ' << ya << ' ' << xb << ' ' << yb << endl;
    }
}
