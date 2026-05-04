// конструктив, формулы, полное бинарное дерево
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n; int q; cin >> n >> q;
    ll root = (n+1)/2;
    ll levels = __lg(n+1);
    vector<ll> start(levels+1, 1), step(levels+1, 2), len(levels+1, (n+1)/2);
    for (int i = 2; i <= levels; i++) {
        start[i] = start[i-1] * 2;
        step[i] = step[i-1] * 2;
        len[i] = len[i-1] / 2;
    }
    auto getPosByNumber = [&](ll u) -> pll {
        // найдём уровень и позицию
        ll level = __lg(n+1);
        for (ll level = levels; level >= 1; level--) {
            // лежит ли "u" на этом уровне?
            ll dist = u - start[level];
            if (dist % step[level] == 0) {
                return {level, dist / step[level]};
            }
        }
        assert(false);
        return pll{-1, -1};
    };
    auto getNumberByPos = [&](ll level, ll pos) -> ll {
        // найдём номер по уровню и позиции
        if (level < 1 || level > levels || pos >= len[level])
            return -1;
        return start[level] + pos * step[level];
    };
    while (q --> 0) {
        ll u; cin >> u;
        string s; cin >> s;
        for (auto it : s) {
            auto [currLevel, currPos] = getPosByNumber(u);
            ll nextLevel, nextPos;
            if (it == 'L') {
                nextLevel = currLevel - 1;
                nextPos = currPos * 2;
            } else if (it == 'R') {
                nextLevel = currLevel - 1;
                nextPos = currPos * 2 + 1;
            } else {
                assert(it == 'U');
                nextLevel = currLevel + 1;
                nextPos = currPos / 2;
            }
            ll nextVert = getNumberByPos(nextLevel, nextPos);
            if (nextVert != -1)
                u = nextVert;
        }
        cout << u << '\n';
    }
}
