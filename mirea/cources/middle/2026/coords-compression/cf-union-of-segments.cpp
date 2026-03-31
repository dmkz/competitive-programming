// сжатие отрезков, корневая декомпозиция
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
int lowpos(const auto &vec, const auto &item) {
    return int(lower_bound(all(vec), item) - vec.begin());
}
main() {
    // читаем вектор из операций + запоминаем координаты, используемые там:
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<tuple<char, ll, ll>> ops(n);
    vector<ll> xx;
    xx.reserve(2 * n);
    for (auto &[ch, L, R] : ops) {
        cin >> ch >> L >> R;
        xx.push_back(L);
        xx.push_back(R);
    }
    // сжатие отрезков на числовой прямой:
    sort(all(xx));
    xx.erase(unique(all(xx)), xx.end());
    vector<pair<ll, ll>> segs;
    segs.reserve(2 * isz(xx));
    for (int i = 0; i < isz(xx); i++) {
        if (i - 1 >= 0) {
            ll prevX = xx[i - 1] + 1;
            ll currX = xx[i] - 1;
            if (prevX <= currX)
                segs.emplace_back(prevX, currX);
        }
        segs.emplace_back(xx[i], xx[i]);
    }
    // создаём корневую декомпозицию:
    vector<int> cnt(isz(segs));
    vector<ll> len;
    len.reserve(isz(segs));
    for (const auto &[L, R] : segs)
        len.emplace_back(R - L + 1);
    const int gsize = 1024;
    const int groups = (isz(segs) + gsize - 1) / gsize;
    vector<int> groupCnt(groups);
    vector<ll> groupLen(groups), groupLocal(groups), groupAnsw(groups);
    for (int i = 0; i < isz(segs); i++)
        groupLen[i / gsize] += len[i];
    // обрабатываем запросы:
    ll answ = 0;
    auto decrease = [&](int gId, int L, int R) {
        answ -= groupAnsw[gId];
        for (int i = L; i <= R; i++) {
            if (groupCnt[gId] == 0 && cnt[i] == 1)
                groupAnsw[gId] -= len[i];
            cnt[i]--;
            if (cnt[i] == 0)
                groupLocal[gId] -= len[i];
        }
        answ += groupAnsw[gId];
    };
    auto increase = [&](int gId, int L, int R) {
        answ -= groupAnsw[gId];
        for (int i = L; i <= R; i++) {
            if (cnt[i] == 0)
                groupLocal[gId] += len[i];
            cnt[i]++;
            if (groupCnt[gId] == 0 && cnt[i] == 1)
                groupAnsw[gId] += len[i];
        }
        answ += groupAnsw[gId];
    };
    for (const auto &[ch, L, R] : ops) {
        const int s = lowpos(segs, pll(L, L));
        const int f = lowpos(segs, pll(R, R));
        const int gs = s / gsize;
        const int gf = f / gsize;
        if (ch == '+') {
            if (gs == gf) {
                increase(gs, s, f);
            } else {
                increase(gs, s, (gs + 1) * gsize - 1);
                increase(gf, gf * gsize, f);
                for (int g = gs + 1; g < gf; g++) {
                    answ -= groupAnsw[g];
                    groupCnt[g]++;
                    groupAnsw[g] = groupLen[g];
                    answ += groupAnsw[g];
                }
            }
        } else {
            assert(ch == '-');
            if (gs == gf) {
                decrease(gs, s, f);
            } else {
                decrease(gs, s, (gs + 1) * gsize - 1);
                decrease(gf, gf * gsize, f);
                for (int g = gs + 1; g < gf; g++) {
                    answ -= groupAnsw[g];
                    groupCnt[g]--;
                    groupAnsw[g] = (groupCnt[g] > 0 ? groupLen[g] : groupLocal[g]);
                    answ += groupAnsw[g];
                }
            }
        }
        cout << answ << '\n';
    }
}
