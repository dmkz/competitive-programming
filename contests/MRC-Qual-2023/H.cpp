#include <bits/stdc++.h>
//#define PLAY_WITH_YOURSELF 1
#define isz(x) (int)(x).size()
using namespace std;
using pii = pair<int,int>;
using vi = vector<int>;
void remin(auto &x, const auto &y) { if (y < x) x = y; }

int delta = 0;

#ifdef PLAY_WITH_YOURSELF
int number = 33;

string getSide(int x) {
    return x <= 36 ? "main" : "side";
}

string getLowHigh(int x) {
    return x % 2 == 0 ? "high" : "low";
}
#endif

auto ask(int x) {
    cout << "? " << x << endl;
    delta += x;
    string fi, se;
    #ifdef PLAY_WITH_YOURSELF
        number += x;
        fi = getLowHigh(number);
        se = getSide(number);
    #else
        cin >> fi >> se;
    #endif   
    return make_pair(fi, se);
}

int main() {
    auto [fi,se] = ask(0);
    vi candidates;
    if (se == "side") {
        // можем вычитать!
        if (fi == "high") candidates = {38,40,42,44,46,48,50,52,54};
        else candidates = {37,39,41,43,45,47,49,51,53};
    } else {
        assert(se == "main");
        // можем прибавлять
        if (fi == "high") {
            for (int x = 2; x <= 36; x+=2)
                candidates.push_back(x);
        } else {
            for (int x = 1; x <= 35; x+=2)
                candidates.push_back(x);
        }
    }
    // нам нужно сделать такой запрос, чтобы половина из кандидатов перевалила
    // за границе между side и main, тогда мы сможем понять, где лежит наше место
    auto getSide = [&](int cand, int x) {
        cand += x;
        return (cand >= 37) ? 1 : 0;
    };
    while (isz(candidates) > 1) {
        pii best(INT_MAX, -55);
        for (int x = -54; x <= 54; x++) {
            int cnt[2]{};
            for (int item : candidates)
                cnt[getSide(item,x)]++;
            remin(best, pii(abs(cnt[1]-cnt[0]), x));
        }
        // спрашиваем для x, который делит кандидатов на половину
        assert(best.second != -55);
        auto [_, x] = best;
        tie (fi, se) = ask(x);
        // сами разбиваем наших кандидатов на половины и оставляем ту, которую
        // сообщила нам система
        vi part[2]{};
        for (int item : candidates)
            part[getSide(item,x)].push_back(item+x);
        candidates = part[(se == "side")];
    }
    assert(isz(candidates) == 1);
    cout << "! " << candidates[0] - delta << endl;
    return 0;
}
