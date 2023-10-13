#include "template.hpp"
#include "numeric.hpp"
const int mod = 3;
using namespace algos::numeric;
using Int = IntMod<mod>;
/*
    1 / 2, 2 / 1, 1 / 1
*/
int main() {
    vpii x;
    {
        int n; std::cin >> n;
        std::set<pii> set;
        for (int p = 1; p <= n; p++)
            for (int q = 1; q <= n; q++) {
                int g = std::gcd(p,q);
                set.insert(pii(p / g, q / g));
            }
        x.assign(all(set));
    }
    vvi adj(isz(x));
    auto toFrac = [&](int i) {
        auto [p,q] = x[i];
        return std::to_string(p) + " / " + std::to_string(q);
    };
    for (int i = 0; i < isz(x); i++)
        for (int j = i+1; j < isz(x); j++) {
            auto [a,b] = x[i];
            auto [c,d] = x[j];
            int num = std::abs(a-c) * std::abs(b-d);
            if (num == 2) {
                //std::cout << toFrac(i) << " <--> " << toFrac(j) << std::endl;
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    
    std::stringstream ss;
    //#define ss std::cout
    vi used(isz(x));
    int answ = 1;
    std::function<void(int,int)> dfs = [&](int u, int p) {
        used[u] = 1;
        for (int v : adj[u]) if (v != p) {
            if (!used[v]) {
                ss << ' ' << toFrac(v);
                answ++;
                dfs(v, u);
                ss << ' ' << toFrac(u);
                answ++;
            }
        }
    };
    ss << toFrac(0);
    dfs(0, -1);
    int sum = std::accumulate(all(used),0);
    if (sum == isz(x)) {
        assert(answ <= (int)2e4);
        std::cout << answ << std::endl;
        std::cout << ss.str() << std::endl;
    } else {
        std::cout << "-1\n";
    }
}
