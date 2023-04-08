#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include "template.hpp"
#include "segmenttree.hpp"
using namespace algos::SegmentTree;
const bool stress = false;
int main() {
    int n, k; std::cin >> n >> k;
    vl a(n); 
    if (stress) {
        std::uniform_int_distribution<ll> dist(0, (ll)1e12L);
        std::mt19937 gen;
        for (auto &it : a)
            it = dist(gen);
    } else std::cin >> a;
    vi pos;
    int nCoords;
    { // сжатие координат
        vl x = a;
        std::sort(all(x));
        std::reuniq(x);
        for (int i = 0; i < n; i++)
            pos << std::lowpos(x, a[i]);
        nCoords = isz(x);
    }
    // инициализируем для k = 2
    vl dpCurr(n);
    auto dpNext = dpCurr;
    ll min = a[0], max = a[0];
    for (int i = 1; i < n; i++) {
        dpCurr[i] = std::max<ll>(std::abs(max-a[i]),std::abs(min-a[i]));
        std::remin(min,a[i]);
        std::remax(max,a[i]);
    }
    SegmentTree<ll, TraitsMaxSet<ll>> segtreeplus;
    SegmentTree<ll, TraitsMaxSet<ll>> segtreeminus;
    segtreeplus.build(vl(nCoords,0));
    segtreeminus.build(vl(nCoords,0));
    const ll INF = (ll)1e18L;
    for (int wave = 2; wave < k; wave++) {
        std::fill(all(segtreeplus.data), -INF);
        std::fill(all(segtreeminus.data), -INF);
        std::fill(all(dpNext), -INF);
        segtreeplus.update(pos[wave-1], a[wave-1] + dpCurr[wave-1]);
        segtreeminus.update(pos[wave-1], -a[wave-1] + dpCurr[wave-1]);
        for (int i = wave; i < n; i++) {
            // среди всех, которые больше текущего:
            // a[j] - a[i] + dp[j] -> находим максимум из dp[j] + a[j]
            // среди всех, которые меньше текущего:
            // a[i] - a[j] + dp[j] -> находим максимум из dp[j] - a[j]
            // два дерева отрезков
            ll res = -INF;
            if (pos[i] > 0)
                std::remax(res,a[i]+segtreeminus.get(0, pos[i]-1));
            std::remax(res,-a[i]+segtreeplus.get(pos[i], nCoords-1));
            dpNext[i] = res;
            segtreeplus.update(pos[i], a[i] + dpCurr[i]);
            segtreeminus.update(pos[i], -a[i] + dpCurr[i]);
        }
        std::swap(dpCurr,dpNext);
    }
    std::cout << *std::max_element(all(dpCurr)) << '\n';
}
