#include "template.hpp"
#include "debug.hpp"
int main() {
    // x, если добавить y до < mod - x, то не переполнится
    // два варианта: минимум на отрезке [0, mod - x - 1]
    // или минимум на отрезке [mod - x, mod - 1]
    // иначе >= mod - x
    int n, mod; std::cin >> n >> mod;
    std::set<pii> fi, se;
    vi removed(n);
    vi val(n);
    for (int i = 0; i < n; i++) {
        int a; std::cin >> a;
        se << pii(a,i);
        val[i] = a;
    }
    auto remove = [&](int iy) {
        assert(removed[iy] == 0);
        auto it = se.find(pii(val[iy],iy));
        assert(it != se.end());
        removed[iy] = 1;
        fi.insert(*it);
        se.erase(it);
    };
    remove(0);
    ll answ{};
    auto getUpdated = [&](int ix) {
        int x = val[ix];
        pii curr(mod+1,-1);
        for (auto cand : {se.begin(), se.lower_bound(pii(mod-x,0))}) {
            if (cand != se.end()) {
                remin(curr,pii((x+cand->first)%mod,cand->second));
            }
        }
        //assert(curr.second != -1);
        return tiii(curr.first, ix, curr.second);
    };
    std::priority_queue<tiii, std::vector<tiii>, std::greater<tiii>> pq;
    pq << getUpdated(0);
    while (isz(se) > 0) {
        auto [delta,x,y] = pq.top();
        pq.pop();
        if (removed[x] != removed[y]) {
            answ += delta;
            remove(y);
            if (isz(se))
                pq << getUpdated(y);
        }
        if (isz(se))
            pq << getUpdated(x);
    }
    std::cout << answ << std::endl;
}